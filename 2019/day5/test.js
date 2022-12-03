const should = require('chai').should()

const compute = require('./index').compute;


describe('calc', function () {
    describe('compute', function () {
        it('should compute', function () {

            compute([1, 0, 0, 0, 99]).should.deep.equal([2, 0, 0, 0, 99])
        });
        it('should compute', function () {
            compute([2, 3, 0, 3, 99]).should.deep.equal([2, 3, 0, 6, 99])
        });
        it('should compute', function () {

            compute([2, 4, 4, 5, 99, 0]).should.deep.equal([2, 4, 4, 5, 99, 9801])
        });
        it('should compute', function () {

            compute([1, 1, 1, 4, 99, 5, 6, 0, 99]).should.deep.equal([30, 1, 1, 4, 2, 5, 6, 0, 99])
        })
    });
});
