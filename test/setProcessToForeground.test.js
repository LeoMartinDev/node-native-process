const assert = require('assert');
const expect = require('chai').expect;
const should = require('chai').should();
const addon = require('../index');

describe('setProcessToForeground', function () {
    it('should fail - no arguments', async function () {
        try {
            await addon.setProcessToForeground()
        } catch (error) {
            expect(error).to.be.an('error');
        }
    });
    it('should fail - "processId" not a number', async function () {
        try {
            await addon.setProcessToForeground('1')
        } catch (error) {
            expect(error).to.be.an('error');
        }
    });
});