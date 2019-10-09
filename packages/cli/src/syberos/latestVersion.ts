import * as url from 'url'
import * as got from 'got'
import * as registryUrl from 'registry-url'
import * as registryAuthToken from 'registry-auth-token'
import * as semver from 'semver'


async function latestVersion(name: string, timeout: number) {
  return packageJson(name.toLowerCase(), timeout).then(data => data.version)
}

async function packageJson(name: string, timeout: number, options: any = {}) {
  const scope = name.split('/')[0];
  const regUrl = registryUrl(scope);
  const pkgUrl = url.resolve(regUrl, encodeURIComponent(name).replace(/^%40/, '@'));
  const authInfo = registryAuthToken(regUrl, { recursive: true });

  options = Object.assign({
    version: 'latest'
  }, options);

  const headers = {
    accept: 'application/vnd.npm.install-v1+json; q=1.0, application/json; q=0.8, */*'
  };

  if (options.fullMetadata) {
    delete headers.accept;
  }

  if (authInfo) {
    headers['authorization'] = `${authInfo.type} ${authInfo.token}`;
  }

  return got(pkgUrl, { json: true, timeout: timeout, headers })
    .then(res => {
      let data = res.body;
      let { version } = options;

      if (options.allVersions) {
        return data;
      }

      if (data['dist-tags'][version]) {
        data = data.versions[data['dist-tags'][version]];
      } else if (version) {
        if (!data.versions[version]) {
          const versions = Object.keys(data.versions);
          version = semver.maxSatisfying(versions, version);

          if (!version) {
            throw new Error('Version doesn\'t exist');
          }
        }

        data = data.versions[version];

        if (!data) {
          throw new Error('Version doesn\'t exist');
        }
      }

      return data;
    })
    .catch(err => {
      if (err.statusCode === 404) {
        throw new Error(`Package \`${name}\` doesn't exist`);
      }

      throw err;
    });
};

export default latestVersion