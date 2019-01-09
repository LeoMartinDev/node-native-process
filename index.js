const testAddon = require('./build/Release/testaddon.node');
console.log('addon',testAddon.getProcessesByName('chrome'));
module.exports = testAddon;