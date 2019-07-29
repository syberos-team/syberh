import { expect } from 'chai';
import osMixin from '../src/core/os';
import {
    setUserAgent,
    setAppVersion,
} from './inner/hackwindow';

const ORIGINAL_NAVIGATOR = navigator.userAgent;
let syber;

describe('H5环境', () => {
    before(() => {
        syber = {};
        osMixin(syber);
    });
    
    it('默认为h5', () => {
        expect(syber.os.h5).to.be.equal(true);
    });

    it('默认其它os都为假', () => {
        expect(syber.os.dd).to.be.equal(undefined);
        expect(syber.os.syber).to.be.equal(undefined);
    });
    
    it('默认非Android与iOS', () => {
        expect(syber.os.android).to.be.equal(undefined);
        expect(syber.os.ios).to.be.equal(undefined);
        
        expect(syber.os.isBadAndroid).to.be.equal(undefined);
        expect(syber.os.ipad).to.be.equal(undefined);
        expect(syber.os.iphone).to.be.equal(undefined);
    });
});

describe('模拟Android', () => {
    const AGENT_ANDROID = 'Android; 1.0.2;';
    const APPVERSION_BAD_ANDROID = 'firefox 50';
    
    before(() => {
        // 在本区块的所有测试用例之前执行
        syber = {};
        
        setUserAgent(AGENT_ANDROID);
        setAppVersion(APPVERSION_BAD_ANDROID);
        
        osMixin(syber);
    });
    
    it('为Android环境', () => {
        expect(syber.os.android).to.be.equal(true);
    });
    
    it('版本匹配', () => {
        expect(syber.os.version).to.be.equal('1.0.2');
    });
    
    it('为badAndroid', () => {
        expect(syber.os.isBadAndroid).to.be.equal(true);
    });
    
    after(() => {
        setUserAgent(ORIGINAL_NAVIGATOR);
    });
});

describe('模拟iphone', () => {
    const AGENT_IPHONE = 'iPhone OS 1_0_1;';
    
    before(() => {
        // 在本区块的所有测试用例之前执行
        syber = {};
        
        setUserAgent(AGENT_IPHONE);
        
        osMixin(syber);
    });
    
    it('为iOS环境', () => {
        expect(syber.os.ios).to.be.equal(true);
    });
    
    it('为iphone环境', () => {
        expect(syber.os.iphone).to.be.equal(true);
    });
    
    it('版本号匹配', () => {
        expect(syber.os.version).to.be.equal('1.0.1');
    });
    
    after(() => {
        setUserAgent(ORIGINAL_NAVIGATOR);
    });
});

describe('模拟ipad', () => {
    const AGENT_IPAD = 'iPad OS 1_0_2;';
    
    before(() => {
        // 在本区块的所有测试用例之前执行
        syber = {};
        
        setUserAgent(AGENT_IPAD);
        
        osMixin(syber);
    });
    
    it('为iOS环境', () => {
        expect(syber.os.ios).to.be.equal(true);
    });
    
    it('为ipad环境', () => {
        expect(syber.os.ipad).to.be.equal(true);
    });
    
    it('版本号匹配', () => {
        expect(syber.os.version).to.be.equal('1.0.2');
    });
    
    after(() => {
        setUserAgent(ORIGINAL_NAVIGATOR);
    });
});

describe('模拟syber、dd与syber', () => {
    const AGENT_syber = 'SyberOSHybrid1.0.1';
    const AGENT_DD = 'DingTalk1.0.1';
    
    before(() => {
        // 在本区块的所有测试用例之前执行
        syber = {};
        
        setUserAgent(AGENT_DD + AGENT_syber);
        
        osMixin(syber);
    });
    
    it('为syber环境', () => {
        expect(syber.os.syber).to.be.equal(true);
    });
    
    it('为DD环境', () => {
        expect(syber.os.dd).to.be.equal(true);
    });
    
    after(() => {
        setUserAgent(ORIGINAL_NAVIGATOR);
    });
});