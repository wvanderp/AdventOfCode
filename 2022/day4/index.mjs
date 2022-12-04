import fs from 'fs';
import path from 'path'

const input = fs.readFileSync(path.join( './input.txt'))
// const input = fs.readFileSync(path.join( './example.txt'))
.toString()
.split('\n')
.map(x=> {
    const [a1, a2] = x.split(',')[0].split('-').map(x=> parseInt(x))
    const [b1, b2] = x.split(',')[1].split('-').map(x=> parseInt(x))
    
    console.log(x, a1,a2,b1,b2)

    if(a1 <= b1 && a2 >= b2){
        return 1;
    }

    if(b1 <= a1 && b2 >= a2) {
        return 1
    }
    return 0;
})
.reduce((acc, x) => acc + x, 0)

console.log(input)

//https://stackoverflow.com/a/10050831
function range(startAt, endAt) {
    const size = endAt - startAt + 1;
    return [...Array(size).keys()].map(i => i + startAt);
}


const input2 = fs.readFileSync(path.join( './input.txt'))
// const input = fs.readFileSync(path.join( './example.txt'))
.toString()
.split('\n')
.map(x=> {
    const [a1, a2] = x.split(',')[0].split('-').map(x=> parseInt(x))
    const [b1, b2] = x.split(',')[1].split('-').map(x=> parseInt(x))
    
    const a = range(a1, a2)
    const b = range(b1, b2)

    const c = a.filter(x=> b.includes(x))

    if (c.length > 0) {
        return 1
    }
    return 0;
})
.reduce((acc, x) => acc + x, 0)

console.log(input2)