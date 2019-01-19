const assert = require('assert');
const expect = require('chai').expect;
const should = require('chai').should();
const addon = require('../index');

describe('getForegroundWindowProcessId', function () {
    it('should fail - no arguments', async function () {
        try {
            await addon.getForegroundWindowPid();
        } catch (error) {
            expect(error).to.be.an('error');
        }
    });
    it('should return a pid', async function () {
        const pid = await addon.getForegroundWindowPid();

        expect(pid).to.be.a('number');
    });
});