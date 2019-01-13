const addon = require('./index.js');

(async () => {
  const processes = await addon.getProcessesByName('Dofus.exe');

  console.log(processes);
})();