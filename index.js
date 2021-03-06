const addon = require('./build/Release/addon.node');

function getProcessesByName(processName) {
    return new Promise((resolve, reject) => {
        try {
            addon.getProcessesByName(processName, function (error, result) {
                if (error) return reject(error);
                return resolve(result);
            });
        } catch (error) {
            reject(error);
        }
    });
};

function getProcessWindowTitle(processId) {
    return new Promise((resolve, reject) => {
        try {
            addon.getProcessWindowTitle(processId, function (error, result) {
                if (error) return reject(error);
                return resolve(result);
            });
        } catch (error) {
            reject(error);
        }
    });
};

function setProcessToForeground(processId) {
    return new Promise((resolve, reject) => {
        try {
            addon.setProcessToForeground(processId, function (error, result) {
                if (error) return reject(error);
                return resolve(result);
            });
        } catch (error) {
            reject(error);
        }
    });
};

function getForegroundWindowPid() {
    return new Promise((resolve, reject) => {
        try {
            addon.getForegroundWindowPid(function (error, result) {
                if (error) return reject(error);
                return resolve(result);
            });
        } catch (error) {
            reject(error);
        }
    });
};

module.exports = {
    getProcessesByName,
    getProcessWindowTitle,
    setProcessToForeground,
    getForegroundWindowPid,
};