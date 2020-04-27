#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import argparse
import os
import sys
import time
from multiprocessing import cpu_count
from string import Template

BIN_PATH = os.path.realpath(__file__)


def commands():
    parser = argparse.ArgumentParser(description='编译syberh项目')

    subparsers_cmd = parser.add_subparsers(dest='cmd', help='commands')

    # clear
    parser_clear = subparsers_cmd.add_parser('clear')
    parser_clear.add_argument('-b', '--build', action='store', required=True,
                        dest='build_path', help='编译输出路径')
                        
    # build
    parser_build = subparsers_cmd.add_parser('build')
    parser_build.add_argument('-p', '--pro', action='store', required=True,
                        dest='pro_path', help='项目主pro文件路径')
    parser_build.add_argument('-b', '--build', action='store', required=True,
                        dest='build_path', help='编译输出路径')
    parser_build.add_argument('-n', '--num', action='store', type=int, required=False,
                        dest='process_num', help='并行编译的进程数')
    parser_build.add_argument('-d', '--pdk', action='store', required=True,
                        dest='pdk_path', help='pdk根目录')
                        
    parser_build.add_argument('-t', '--target', action='store', required=True,
                        dest='target_name', help='target名称')   
    parser_build.add_argument('--args', action='append', required=False,
                        dest='args', help='qmake额外参数') 
                                   
    # install
    parser_install = subparsers_cmd.add_parser('install')
    parser_install.add_argument('-s', '--sop', action='store', required=True,
                        dest='sop_path', help='sop包路径')
                        
    # rename
    parser_rename = subparsers_cmd.add_parser('rename')
    parser_rename.add_argument('-s', '--sop', action='store', required=True,
                        dest='sop_path', help='改名的sop包路径')
                        
    return parser


def run_commands(cmds = {}):
    parser = commands()
    args = parser.parse_args()

    if not args.cmd:
        print(parser.print_help())
        raise SystemExit(1)

    for sub_cmd, cmd_func in cmds.items():
        if sub_cmd == args.cmd:
            cmd_func(args)


def search_sop(build_path):
    if not os.path.exists(build_path):
        return None
    for f in os.listdir(build_path):
        if f.endswith('.sop'):
            return f


def is_support_pexpect():
    py_verion = sys.version_info
    return py_verion.major >= 3 and py_verion.minor >= 5


def need_package_sop(pro_path):
    pro_dir = os.path.dirname(pro_path)
    xml_path = os.path.join(pro_dir, 'sopconfig.xml')
    return os.path.exists(xml_path) and os.path.isfile(xml_path)

def scp_sop(sop_path):
    if not os.path.exists(sop_path):
        print('未找到sop包: ' + sop_path)
        raise SystemExit(1)
    
    if not is_support_pexpect():
        os.system('/usr/bin/expect ./syberh-scp ' + sop_path)
        return

    import pexpect

    child = pexpect.spawn('scp ' + sop_path + ' developer@192.168.100.100:/tmp', encoding='utf-8')
    child.logfile = sys.stdout
    index = child.expect(["(?i)password:", '(?i)Are you sure you want to continue connecting', 
                            pexpect.EOF, pexpect.TIMEOUT])
    if index == 0:
        child.sendline('system')
        child.expect(pexpect.EOF)
    elif index == 1:
        child.sendline('yes')
        index = child.expect( ['(?i)password:', pexpect.EOF, pexpect.TIMEOUT] )
        if index == 0:
            child.sendline('system')
            child.expect(pexpect.EOF)
    child.close()


def build(args):
    if not os.path.exists(args.build_path):
        os.makedirs(args.build_path)
    if not os.path.exists(args.pro_path) and not os.path.isfile(args.pro_path):
        print('未找到pro文件：' + args.pro_path)
        raise SystemExit(1)
    if not os.path.exists(args.pdk_path):
        print('未安装pdk，不存在的位置：' + args.pdk_path)
        raise SystemExit(1)

    os.chdir(args.build_path)

    kchroot_path = os.path.join(args.pdk_path, 'sdk/script/kchroot')
    target_full_name = args.target_name
    qmake_path = '/usr/lib/qt5/bin/qmake'
    process_num = args.process_num
    if not process_num:
        process_num = cpu_count()

    qmake_args = ''
    if args.args and len(args.args) > 0:
        qmake_args = ' '.join(args.args)
    qmake_args = qmake_args.rstrip()

    cmd_setup1 = Template("${kchroot_path} 'sb2 -t ${target_full_name} -R' '${qmake_path} ${pro_path} -r -spec linux-g++ CONFIG+=qml_debug ${qmake_args}'") \
                .substitute(kchroot_path=kchroot_path, target_full_name=target_full_name, qmake_path=qmake_path, pro_path=args.pro_path, qmake_args=qmake_args)

    cmd_setup2 = Template("${kchroot_path} 'sb2 -t ${target_full_name} -R' '/usr/bin/make -j${process_num}'") \
                .substitute(kchroot_path=kchroot_path, target_full_name=target_full_name, process_num=process_num)

    cmd_setup3 = Template("${kchroot_path} 'sb2 -t ${target_full_name} -R' 'buildpkg ${pro_path}'") \
                .substitute(kchroot_path=kchroot_path, target_full_name=target_full_name, pro_path=args.pro_path)

    os.system(cmd_setup1)
    os.system(cmd_setup2)
    if need_package_sop(args.pro_path):
        os.system(cmd_setup3)


def clear(args):
    if os.path.exists(args.build_path):
        print('开始清理目录：' + args.build_path)
        time.sleep(1)
        os.system('rm -rf ' + args.build_path + '/*')
    else:
        print('清理的目录不存在：' + args.build_path)


def install(args):
    if not os.path.exists(args.sop_path) or not os.path.isfile(args.sop_path):
        print('sop不存在：', args.sop_path)
        raise SystemExit(1)
    if not args.sop_path.endswith('.sop'):
        print('不是sop包：', args.sop_path)
        raise SystemExit(1)
    scp_sop(args.sop_path)


def rename(args):
    if not os.path.exists(args.sop_path) or not os.path.isfile(args.sop_path):
        print('sop不存在：', args.sop_path)
        raise SystemExit(1)

    sop_dir = os.path.dirname(args.sop_path)
    sop_filename = os.path.basename(args.sop_path)
    new_sop_filename = sop_filename.rstrip('.sop') + '.tar.gz'
    os.rename(args.sop_path, os.path.join(sop_dir, new_sop_filename))


if __name__ == '__main__':
    run_commands({
        'build': build,
        'clear': clear,
        'install': install,
        'rename': rename
    })
