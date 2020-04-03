/**
 * 不用pollyfill，避免体积增大
 */
import hybridJs from '../hybrid';

export default function promiseMixin() {
    hybridJs.Promise = window.Promise;

    hybridJs.getPromise = () => hybridJs.Promise;

    hybridJs.setPromise = (newPromise) => {
        hybridJs.Promise = newPromise;
    };
}