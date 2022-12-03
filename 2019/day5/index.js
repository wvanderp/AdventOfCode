// instructions
function add(pr) {
    return pr[0] + pr[1]
}

function multiply(pr) {
    return pr[0] * pr[1]

}

async function read() {
    try {
        const readline = require('readline');

        const rl = readline.createInterface({
            input: process.stdin,
            output: process.stdout
        });

        const awnser = await new Promise( (resolve, reject) => {
            const readline = require('readline');

            const rl = readline.createInterface({
                input: process.stdin,
                output: process.stdout
            });

            rl.question('What do you think of Node.js? ', (answer) => {
                // TODO: Log the answer in a database
                console.log(`Thank you for your valuable feedback: ${answer}`);
                resolve(answer)
                rl.close();
            });
        })
        return awnser
    } catch (e) {
        console.error(e);
        process.exit(1);
    }

}

function write(rtn) {

}

// helper functions

function numberToArray(number) {
    return number.toString().split('').map(parseNumber);
}

//https://stackoverflow.com/questions/22015684/how-do-i-zip-two-arrays-in-javascript
const zip = (arr1, arr2) => arr1.map((k, i) => [k, arr2[i]]);

function parseNumber(n) {
    return parseInt(n, 10)
}

function fixPr(s, [prType, pr]) {
    if (prType === 0) {
        return parseNumber(s[pr])
    } else if (prType === 1) {
        return pr
    }
}


async function compute(sequence) {
    let pc = 0;


    while (true) {
        const opcode = numberToArray(sequence[pc]);
        const oc = parseNumber(opcode.slice(-2).join(''));
        const prtype = opcode.slice(0, -2).reverse();
        const prCount = prtype.length;

        const prs = zip(prtype, sequence.slice(pc+1 , pc+prCount+1).map(parseNumber)).map((p) => fixPr(sequence, p));
        const rtn = parseNumber(sequence[pc + prCount + 1]);

        switch (oc) {
            case 1:
                sequence[rtn] = add(prs);
                break;
            case 2:
                sequence[rtn] = multiply(prs);
                break;
            case 3:
                console.log(prs, rtn)
                sequence[rtn] = await read();
                break;
            case 4:
                console.log(prs, rtn)
                console.log(write(rtn));
                break;
            case 99:
                //end
                return sequence
        }
        pc += prCount + 2;
    }
}


( async () => {
    const fs = require('fs');
    const input = (fs.readFileSync('./input.txt').toString())
        .split(',');

    // compute(['1002', '4', '3', '4', '33']);
    await compute(input);
})();

module.exports = {
    compute
};
