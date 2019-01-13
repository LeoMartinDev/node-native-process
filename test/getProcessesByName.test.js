const assert = require('assert');
const expect = require('chai').expect;
const should = require('chai').should();
const addon = require('../build/Release/testaddon.node');

describe('getProcessesByName', function() {
    it('should fail - no arguments', function() {
        expect(() => addon.getProcessesByName())
            .to.throw();
    });
    it('should fail - "processName" not a string', function() {
        expect(() => addon.getProcessesByName(1, function (error, result) {}))
            .to.throw();
    });
    it('should fail - "callback" not a function', function() {
        expect(() => addon.getProcessesByName('node'))
            .to.throw();
    });
    it('should return an array', function() {
        addon.getProcessesByName('node', function (error, result) {
            expect(result).to.be.a('array');
        });
    });
});