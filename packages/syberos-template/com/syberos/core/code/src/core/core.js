/*
Yuanxin is pleased to support the open source community by making Syber available.

Copyright (C) 2019 THL A29 Limited, a Yuanxin company. All rights reserved.

Licensed under the MIT License (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at
http://opensource.org/licenses/MIT

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.
*/

/**
 * Syber core class
 */

import pkg from '../../package.json'
import * as tool from '../lib/tool.js'

// built-in plugins
import SyberDefaultPlugin from '../log/log.js'

class Syber {
  constructor (opt) {
    let that = this

    this.version = pkg.version
    this.$dom = null

    this.isInited = false
    this.option = {
      defaultPlugins: ['system', 'network', 'element', 'storage']
    }

    console.log('\n ----init syberos \r\n')

    this.activedTab = ''
    this.tabList = []
    this.pluginList = {}

    this.switchPos = {
      x: 10, // right
      y: 10, // bottom
      startX: 0,
      startY: 0,
      endX: 0,
      endY: 0
    }

    // export helper functions to public
    this.tool = tool

    // merge options
    if (tool.isObject(opt)) {
      for (let key in opt) {
        this.option[key] = opt[key]
      }
    }

    // add built-in plugins
    this._addBuiltInPlugins()

    that._render()
    // try to init
    // let _onload = function () {
    //   if (that.isInited) {
    //     return
    //   }

    //   that._mockTap()
    //   that._bindEvent()
    //   that._autoRun()
    // }
  }

  /**
   * add built-in plugins
   */
  _addBuiltInPlugins () {
    // add default log plugin
    this.addPlugin(new SyberDefaultPlugin('default', 'Log'))

    // add other built-in plugins according to user's config
    const list = this.option.defaultPlugins
    const plugins = {
      system: { proto: SyberDefaultPlugin, name: 'System' }
    }
    if (!!list && tool.isArray(list)) {
      for (let i = 0; i < list.length; i++) {
        let tab = plugins[list[i]]
        if (tab) {
          this.addPlugin(new tab.proto(list[i], tab.name))
        } else {
          console.debug('Unrecognized default plugin ID:', list[i])
        }
      }
    }
  }

  /**
   * render panel DOM
   * @private
   */
  _render () {}

  /**
   * bind DOM events
   * @private
   */
  _bindEvent () {}

  /**
   * auto run after initialization
   * @private
   */
  _autoRun () {
    this.isInited = true

    // init plugins
    for (let id in this.pluginList) {
      this._initPlugin(this.pluginList[id])
    }
    this.triggerEvent('ready')
  }

  /**
   * trigger a Syber.option event
   * @protect
   */
  triggerEvent (eventName, param) {
    eventName = 'on' + eventName.charAt(0).toUpperCase() + eventName.slice(1)
    if (tool.isFunction(this.option[eventName])) {
      this.option[eventName].apply(this, param)
    }
  }

  /**
   * init a plugin
   * @private
   */
  _initPlugin (plugin) {
    plugin.Syber = this
    // start init
    plugin.trigger('init')
    // render tab (if it is a tab plugin then it should has tab-related events)
    plugin.trigger('renderTab', function (tabboxHTML) {})
    // render top bar
    plugin.trigger('addTopBar', function (btnList) {})
    // render tool bar
    plugin.trigger('addTool', function (toolList) {})
    // end init
    plugin.isReady = true
    plugin.trigger('ready')
  }

  /**
   * trigger an event for each plugin
   * @private
   */
  _triggerPluginsEvent (eventName) {
    for (let id in this.pluginList) {
      if (this.pluginList[id].isReady) {
        this.pluginList[id].trigger(eventName)
      }
    }
  }

  /**
   * trigger an event by plugin's name
   * @private
   */
  _triggerPluginEvent (pluginName, eventName) {
    let plugin = this.pluginList[pluginName]
    if (!!plugin && plugin.isReady) {
      plugin.trigger(eventName)
    }
  }

  /**
   * add a new plugin
   * @public
   * @param object VConsolePlugin object
   * @return boolean
   */
  addPlugin (plugin) {
    // ignore this plugin if it has already been installed
    if (this.pluginList[plugin.id] !== undefined) {
      console.debug('Plugin ' + plugin.id + ' has already been added.')
      return false
    }
    this.pluginList[plugin.id] = plugin
    // init plugin only if Syber is ready
    if (this.isInited) {
      this._initPlugin(plugin)
      // if it's the first plugin, show it by default
      if (this.tabList.length === 1) {
        this.showTab(this.tabList[0])
      }
    }
    return true
  }

  /**
   * remove a plugin
   * @public
   * @param string pluginID
   * @return boolean
   */
  removePlugin (pluginID) {
    pluginID = (pluginID + '').toLowerCase()

    return true
  }

  /**
   * show console panel
   * @public
   */
  show () {
    if (!this.isInited) {
      return
    }

    // set 10ms delay to fix confict between display and transition
    setTimeout(function () {}, 10)
  }

  /**
   * hide console panel
   * @public
   */
  hide () {
    if (!this.isInited) {
    }
  }

  /**
   * show switch button
   * @public
   */
  showSwitch () {
    if (!this.isInited) {
    }
  }

  /**
   * hide switch button
   */
  hideSwitch () {
    if (!this.isInited) {
    }
  }

  /**
   * show a tab
   * @public
   */
  showTab (tabID) {}

  /**
   * update option(s)
   * @public
   */
  setOption (keyOrObj, value) {
    if (tool.isString(keyOrObj)) {
      this.option[keyOrObj] = value
      this._triggerPluginsEvent('updateOption')
    } else if (tool.isObject(keyOrObj)) {
      for (let k in keyOrObj) {
        this.option[k] = keyOrObj[k]
      }
      this._triggerPluginsEvent('updateOption')
    } else {
      console.debug(
        'The first parameter of Syber.setOption() must be a string or an object.'
      )
    }
  }

  /**
   * uninstall Syber
   * @public
   */
  destroy () {
    if (!this.isInited) {
      return
    }
    // remove plugins
    let IDs = Object.keys(this.pluginList)
    for (let i = IDs.length - 1; i >= 0; i--) {
      this.removePlugin(IDs[i])
    }
    // reverse isInited when destroyed
    this.isInited = false
  }
} // END class

export default Syber
