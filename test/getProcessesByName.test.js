const assert = require('assert');
const expect = require('chai').expect;
const should = require('chai').should();
const addon = require('../index');

describe('getProcessesByName', function () {
    it('should fail - no arguments', async function () {
        try {
            await addon.getProcessesByName()
        } catch (error) {
            expect(error).to.be.an('error');
        }
    });
    it('should fail - "processName" not a string', async function () {
        try {
            await addon.getProcessesByName(1)
        } catch (error) {
            expect(error).to.be.an('error');
        }
    });
    it('should return an array', async function () {
            const pids = await addon.getProcessesByName('node.exe');

            expect(pids).to.be.an('array');
    });
    it('should find current pid', async function () {
        const pids = await addon.getProcessesByName('node.exe');

        expect(pids).to.include(process.pid);
    });
});