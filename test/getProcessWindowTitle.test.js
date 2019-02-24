const assert = require('assert');
const expect = require('chai').expect;
const should = require('chai').should();
const addon = require('../index');
const path = require('path');
const {
    spawn
} = require('child_process');
const {
    spawnTestApp,
    mapPromise,
} = require('./lib/helpers');

describe('getProcessWindowTitle', function () {
    let electronProcess;
    let electronProcessId;

    beforeEach('starting sample app', async () => {
        [ electronProcess, electronProcessId ] = await spawnTestApp();
    });

    afterEach('killing sample app', (done) => {
        if (electronProcess) {
            electronProcess.kill();
            process.kill(electronProcessId);
            electronProcess = null;
        }
        setTimeout(done, 1000);
    });

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
    it('should fail - no window title', async function () {
        try {
            const pids = await addon.getProcessesByName('node.exe');
            const title = await addon.getProcessWindowTitle(pids[0]);
        } catch (error) {
            expect(error).to.be.an('error');
        }
    });
    it('should find "native-process-test"', async function () {
        try {
            const windowTitle = await addon.getProcessWindowTitle(electronProcessId);

            expect(windowTitle).to.be.equal('native-process-test');
        } catch (error) {
            expect(error).to.be.undefined();
        }
    }).timeout(7000);
});