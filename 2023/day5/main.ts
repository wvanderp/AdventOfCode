import fs from 'fs';
import path from 'path';

const input = fs.readFileSync(path.join(__dirname, 'input.txt'), 'utf-8');

// parse input

// split on empty lines
const sections = input.split('\n\n');

console.log(sections);

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


console.log(stsi);
function mapTo(from: Rule[], n: number): number {
    for (const r of from) {
        // match range
        if (n >= r.source && n <= r.source + r.range) {
            // map to destination
            return r.destination + (n - r.source);
        }

    }
    return n;
}  

const seedLocations = seeds.map(s => ruleMaps.reduce((acc, rules) => mapTo(rules, acc), s));

console.log(Math.min(...seedLocations));

