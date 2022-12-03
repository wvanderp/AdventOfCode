const correct = []
const R = require('ramda');
for (let a = 145852; a < 616942; a++) {
    const aa = a.toString().split('')
    if (JSON.stringify([...aa].sort((a, b) => a - b)) === JSON.stringify(aa)) {
        const groups = R.groupWith(R.equals, aa)
        if(R.any((r) => r.length === 2)(groups)){
            correct.push(aa)
        }
    }

}
// console.log(correct.length)

const part1 = R.length(R.filter((r)=> R.any((r) => r.length > 1)(R.groupWith(R.equals, r)),R.filter((r) => R.equals(R.sortBy(R.identity, r), r), R.map((r) => R.splitEvery(1, r.toString()), R.range(145852, 616942)))));
const part2 = R.length(R.filter((r)=> R.any((r) => r.length === 2 )(R.groupWith(R.equals, r)),R.filter((r) => R.equals(R.sortBy(R.identity, r), r), R.map((r) => R.splitEvery(1, r.toString()), R.range(145852, 616942)))));
console.log(part1, part2)
