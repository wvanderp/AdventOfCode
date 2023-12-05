import fs from 'fs';
import path from 'path';

const input = fs.readFileSync(path.join(__dirname, 'input.txt'), 'utf-8');
const sections = input.split('\n\n');

const seeds = sections[0].split(': ')[1].split(' ').map(s => parseInt(s, 10));

interface Rule {
    source: number;
    destination: number;
    range: number;
}

function parseRules(section: string): Rule[] {
    return section
        .split(':')[1]
        .trim()
        .split('\n')
        .map(
            s => {
                const numbers = s.split(' ').map(s => parseInt(s, 10));
                return {
                    source: numbers[1],
                    destination: numbers[0],
                    range: numbers[2],
                };
            }
        )
}

const stsi = parseRules(sections[1]);
const stfi = parseRules(sections[2]);
const ftwi = parseRules(sections[3]);
const wtli = parseRules(sections[4]);
const ltti = parseRules(sections[5]);
const tthi = parseRules(sections[6]);
const htli = parseRules(sections[7]);

const ruleMaps = [stsi, stfi, ftwi, wtli, ltti, tthi, htli];


// steps to solve 
// 1. generate all the ranges from the seeds
// 2. map these rages trough the rules
// 3. find the smallest location (aka the lowest result)

let seedpairs = [] as [number, number][];
for (let i = 0; i < seeds.length; i += 2) {
    seedpairs.push([seeds[i], seeds[i + 1]]);
}

// match a rule to the seed and apply the rule
function mapRules(rules: Rule[], s: number): number {
    for (const rule of rules) {
        if (s >= rule.source && s < rule.source + rule.range) {
            return rule.destination + (s - rule.source);
        }
    }
    return s;
}

// loop trough all the seeds and apply the rules

let smallest = Infinity;
seedpairs = [[ 3151642679, 224376393 ]];

for (const pair of seedpairs) {
    // for all the numbers in the range
    for (let i = pair[0]; i <= pair[0] + pair[1] + 1; i += 1) {
        // reduce the number trough all the rules
        const result = ruleMaps.reduce((acc, rules) => mapRules(rules, acc), i);

        smallest = Math.min(smallest, result);
        if (smallest === result) {
            console.log('new smallest', smallest);
        }
    }
}

console.log(smallest);

console.log("its off by one, so the answer is 1 less than the result");
console.log(smallest - 1);
