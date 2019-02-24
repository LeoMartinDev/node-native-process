const assert = require('assert');
const expect = require('chai').expect;
const should = require('chai').should();
const addon = require('../index');
const { spawnTestApp } = require('./lib/helpers');

describe('getForegroundWindowPid', function () {
    let electronProcess;
    let electronProcessId;

    beforeEach('starting sample app', (done) => {
        spawnTestApp.then(result => {
            electronProcess = result.electronProcess;
            electronProcessId = result.electronProcessId;
            done();
        })
        .catch(done);
    });

    afterEach('killing sample app', (done) => {
        if (electronProcess) {
            electronProcess.kill();
            process.kill(electronProcessId);
            electronProcess = null;
        }
        done();
    });

    it('should fail - no arguments', async function () {
        try {
            await addon.getForegroundWindowPid();
        } catch (error) {
            expect(error).to.be.an('error');
        }
    });
    it('should return a pid', async function () {
        const pid = await addon.getForegroundWindowPid();

        expect(pid).to.be.equal(electronProcessId);
    });
});