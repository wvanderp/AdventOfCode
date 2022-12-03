const fs = require('fs');

function line_intersect(x1, y1, x2, y2, x3, y3, x4, y4) {
    var ua, ub, denom = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
    if (denom === 0) {
        return null;
    }
    ua = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / denom;
    ub = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / denom;
    return {
        x: x1 + ua * (x2 - x1),
        y: y1 + ua * (y2 - y1),
        seg1: ua >= 0 && ua <= 1,
        seg2: ub >= 0 && ub <= 1
    };
}

// let [i1, i2] = (fs.readFileSync('./input.txt').toString())
//     .split('\n');

let i1 = 'R75,D30,R83,U83,L12,D49,R71,U7,L72';
let i2 = 'U62,R66,U55,R34,D71,R55,D58,R83';

// let i1 = 'R4,U2,L5';
// let i2 = 'U3,R2,D5';



i1 = i1.split(',').map((r) => [r.substr(0, 1), parseInt(r.substr(1), 10)]);
i2 = i2.split(',').map((r) => [r.substr(0, 1), parseInt(r.substr(1), 10)]);


const lines = [];


let x = 0;
let y = 0;
let ox = 0;
let oy = 0;
let steps = 0;

for (let i = 0; i < i1.length; i++) {
    const opCode = i1[i][0];
    const amount = i1[i][1];
    [ox, oy] = [x, y];

    switch (opCode) {
        case 'U':
            y += amount;
            break;
        case 'D':
            y -= amount;
            break;
        case 'L':
            x -= amount;
            break;
        case 'R':
            x += amount;
            break;
    }

    steps += amount;
    lines.push({ox, oy, x, y, stepsAfter: steps})


}

console.log(lines)


x = 0;
y = 0;
ox = 0;
oy = 0;
steps = 0;

let intersections = [];

for (let i = 0; i < i2.length; i++) {
    const opCode = i2[i][0];
    const amount = i2[i][1];
    [ox, oy] = [x, y];

    switch (opCode) {
        case 'U':
            y += amount;
            break;
        case 'D':
            y -= amount;
            break;
        case 'L':
            x -= amount;
            break;
        case 'R':
            x += amount;
            break;
    }

    steps += amount;

    for (let j = 0; j < i1.length; j++) {
        const l1 = lines[j];
        const intersect = line_intersect(l1.ox, l1.oy, l1.x, l1.y, ox, oy, x, y);
        if (intersect !== null) {
            if (intersect.x === 0 && intersect.y === 0) continue;
            if (!intersect.seg1 || !intersect.seg2) continue;
            console.log(l1.stepsAfter , steps)
            intersect.totalsteps = l1.stepsAfter + steps;
            intersections.push(intersect)
        }
    }


}

// console.log(intersections);


//<editor-fold desc="P1">
function manhattanDistance(x1, y1, x2, y2) {
    return Math.abs(x1 - x2) + Math.abs(y1 - y2);
}

let winner = null
let score = Infinity;

for (let i = 0; i < intersections.length; i++) {
    const distance = manhattanDistance(0, 0, intersections[i].x, intersections[i].y);
    if (Math.min(score, distance) === distance) {
        winner = intersections[i];
        winner.distance = distance
        score = distance;
    }
}

console.log('P1', winner.distance)
//</editor-fold>

//<editor-fold desc="P2">
for (let i = 0; i < intersections.length; i++) {
    if (Math.min(score, intersections[i].totalsteps) === intersections[i].totalsteps) {
        winner = intersections[i];
        winner.steps = intersections[i].totalsteps
        score =  winner.steps;
    }
}

console.log(winner)
//</editor-fold>
