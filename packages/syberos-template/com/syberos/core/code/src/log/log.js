/*
Tencent is pleased to support the open source community by making vConsole available.

Copyright (C) 2017 THL A29 Limited, a Tencent company. All rights reserved.

Licensed under the MIT License (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at
http://opensource.org/licenses/MIT

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.
*/

/**
 * vConsole Basic Log Tab
 */

import SyberPlugin from '../lib/plugin.js'

const DEFAULT_MAX_LOG_NUMBER = 1000
const ADDED_LOG_TAB_ID = []

class VConsoleLogTab extends SyberPlugin {
  static AddedLogID = []

  constructor (...args) {
    super(...args)
    ADDED_LOG_TAB_ID.push(this.id)

    this.allowUnformattedLog = true // `[xxx]` format log

    this.isReady = false
    this.isShow = false
    this.console = {}
    this.logList = [] // save logs before ready
    this.isInBottom = true // whether the panel is in the bottom
    this.maxLogNumber = DEFAULT_MAX_LOG_NUMBER
    this.logNumber = 0

    this.mockConsole()
  }

  /**
   * when vConsole is ready,
   * this event will be triggered (after 'add' event)
   * @public
   */
  onInit () {}

  /**
   * this event will make this plugin be registered as a tab
   * @public
   */
  onRenderTab (callback) {
    callback(this.$tabbox)
  }

  onAddTopBar (callback) {}

  onAddTool (callback) {
    let that = this
    let toolList = [
      {
        name: 'Clear',
        global: false,
        onClick: function () {
          that.clearLog()
          that.vConsole.triggerEvent('clearLog')
        }
      }
    ]
    callback(toolList)
  }

  /**
   * after init
   * @public
   */
  onReady () {
    let that = this
    that.isReady = true
  }

  /**
   * before remove
   * @public
   */
  onRemove () {}

  onShow () {
    this.isShow = true
  }

  onHide () {
    this.isShow = false
  }

  onUpdateOption () {
    if (this.vConsole.option.maxLogNumber !== this.maxLogNumber) {
      this.updateMaxLogNumber()
      this.limitMaxLogs()
    }
  }

  updateMaxLogNumber () {
    this.maxLogNumber =
      this.vConsole.option.maxLogNumber || DEFAULT_MAX_LOG_NUMBER
    this.maxLogNumber = Math.max(1, this.maxLogNumber)
  }

  limitMaxLogs () {}

  showLogType (logType) {}

  /**
   * print a log to log box
   * @protected
   * @param  string  _id        random unique id
   * @param  string  tabName    default|system
   * @param  string  logType    log|info|debug|error|warn
   * @param  array   logs       `logs` or `content` can't be empty
   * @param  object  content    `logs` or `content` can't be empty
   * @param  boolean noOrigin
   * @param  int     date
   * @param  string  style
   */
  printLog (item) {}
} // END class

export default VConsoleLogTab
