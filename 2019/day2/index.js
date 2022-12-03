function add(s, pc) {
    s[s[pc + 3]] = s[s[pc + 1]] + s[s[pc + 2]]
}

function multiply(s, pc) {
    s[s[pc + 3]] = s[s[pc + 1]] * s[s[pc + 2]]

}

function compute(sequence) {
    let pc = 0;
    while (true) {
        let opcode = sequence[pc];

        switch (opcode) {
            case 1:
                add(sequence, pc);
                break;
            case 2:
                multiply(sequence, pc);
                break;
            case 99:
                //end
                return sequence
        }
        pc += 4
    }
}


(() => {
    const fs = require('fs');
    const input = (fs.readFileSync('./input.txt').toString())
        .split(',').map((x) => parseInt(x, 10));



    for (let i = 0; i < 99; i++) {
        for (let j = 0; j < 99; j++) {
            const newinput = [...input]
            newinput[1] = i;
            newinput[2] = j;
            const out = compute(newinput);

            if (out[0] === 19690720){
                console.log(100 * i + j )
            }

        }
    }
})();

module.exports = {
    compute
};
