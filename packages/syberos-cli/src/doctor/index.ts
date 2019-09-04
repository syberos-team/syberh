import pdkSdkValidator from './pdkSdkValidator'
import packageValidator from './packageValidator'

export default {
  validators: [
    pdkSdkValidator,
    // configValidator,
    packageValidator
    // recommandValidator,
    // eslintValidator
  ]
}
