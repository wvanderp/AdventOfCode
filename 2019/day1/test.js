const should = require('chai').should()

const calcFuelByMass = require('./index').calcFuelByMass;
const calcFuelForFuel = require('./index').calcFuelForFuel;
const fuelForModule = require('./index').fuelForModule;

describe('lanche', function () {
    describe('calcFuelByMass', function () {
        it('12 should be 2', function () {
            calcFuelByMass(12).should.equal(2);
        });
        it('14 should be 2', function () {
            calcFuelByMass(14).should.equal(2);
        });
        it('1969 should be 654', function () {
            calcFuelByMass(1969).should.equal(654);
        });
        it('100756 should be 33583', function () {
            calcFuelByMass(100756).should.equal(33583);
        });
    });

    describe('calcFuelForFuel', function () {
        it('2 should be 0', function () {
            calcFuelForFuel(2).should.equal(0);
        });
        it('14 should be 2', function () {
            calcFuelForFuel(14).should.equal(2);
        });
        it('654  should be 312', function () {
            calcFuelForFuel(654 ).should.equal(216 + 70 + 21 + 5);
        });
    });

    describe('fuelForModule', function () {
        it('14 should be 2', function () {
            fuelForModule([14]).should.equal(2);
        });
        it('1969 should be 966', function () {
            fuelForModule([1969] ).should.equal(966);
        });
        it('100756 should be 50346', function () {
            fuelForModule([100756] ).should.equal(50346);
        });
    });

    describe('right awser', function () {
        it('give the right awser', function () {
            const masses = [120588, 137636, 114877, 118328, 97394, 58497, 139343, 80307, 125063, 70956, 119676, 76115, 91916, 64618, 82881, 57000, 141785, 73460, 68992, 125701, 97839, 137800, 111051, 104591, 114396, 60210, 80238, 112009, 70265, 140582, 58765, 96848, 130438, 55615, 53903, 109361, 129512, 75888, 93231, 54697, 125320, 53614, 87173, 71762, 147739, 131840, 123979, 54434, 121517, 113518, 83544, 124924, 76608, 130483, 149285, 134147, 111589, 88174, 136392, 94448, 139244, 54064, 85110, 102985, 95646, 54649, 129755, 135795, 119653, 147633, 108386, 143180, 126587, 119273, 130579, 56006, 83232, 99948, 147711, 83092, 99706, 98697, 143231, 94526, 53102, 86002, 71413, 111054, 147220, 136504, 59308, 61123, 148771, 113986, 55483, 94426, 62791, 100959, 63604, 112511]

            fuelForModule(masses).should.equal(5041680);
        });
    });

});
