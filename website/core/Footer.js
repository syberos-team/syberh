/**
 * Copyright (c) 2017-present, Facebook, Inc.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

const React = require('react')
class Footer extends React.Component {
  render() {
    return (
      <footer className="footer" id="footer">
        <div className="footer-container">
          <div className="footer-logo-container">
            <div className="footer-logo" />
          </div>
          <div className="footer-link-container">
            <div className="footer-link">
              <h3>相关资源</h3>
              <p>
                <a className="link" href="#">
                  SyberOS-开发文档
                </a>
              </p>
            </div>
            <div className="footer-link">
              <h3>社区</h3>
              <p>
                <a href="https://github.com/syberos-team/syberos-hybrid/issues">
                  反馈建议
                </a>
              </p>
              <p>
                <a href="https://github.com/syberos-team/syberos-hybrid">
                  GitHub
                </a>
              </p>
            </div>
            <div className="footer-link">
              <h3>关于我们</h3>
              <p>
                <a
                  target="_blank"
                  href="http://www.syberos.com/Introductio/index/id/1250"
                >
                  元心科技
                </a>
              </p>
            </div>
          </div>
        </div>
      </footer>
    )
  }
}

module.exports = Footer
