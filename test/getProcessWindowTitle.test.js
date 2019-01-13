const assert = require('assert');
const expect = require('chai').expect;
const should = require('chai').should();
const addon = require('../index');

describe('getProcessWindowTitle', function () {
    it('should fail - no arguments', async function () {
        try {
            await addon.getProcessWindowTitle()
        } catch (error) {
            expect(error).to.be.an('error');
        }
    });
    it('should fail - "processId" not a number', async function () {
        try {
            await addon.getProcessWindowTitle('1')
        } catch (error) {
            expect(error).to.be.an('error');
        }
    });
    it('should return a string', async function () {
        const pids = await addon.getProcessesByName('node.exe');
        const title = await addon.getProcessWindowTitle(pids[0]);

        expect(title).to.be.a('string');
    });
});