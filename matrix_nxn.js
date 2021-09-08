const readline = require("readline");

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
});

function multiply(matrix1, matrix2, size) {
    m = new Array(size);
    for (let r = 0; r < size; ++r) {
        m[r] = new Array(size);
        for (let c = 0; c < size; ++c) {
            m[r][c] = 0;
            for (let i = 0; i < size; ++i) {
                m[r][c] += matrix1[r][i] * matrix2[i][c];
            }
        }
    }
    for (let i = 0; i < size; i++) {
        var temp = '';
        for (let j = 0; j < size; j++) {
            temp += m[i][j] + ' ';
        }
        // console.log(temp);
    }
    // console.log("---------------------------------------------------------");
};

class Matrix {
    constructor(size, data = []) {
        this.size = size;
        this.data = data;
    };

    get_data() {
        for (let i = 0; i < this.size; i++) {
            var temp = '';
            for (let j = 0; j < this.size; j++) {
                temp += this.data[i][j] + ' ';
            }
            console.log(temp);
        }
        console.log('----------------------------');
    }
    create() {
        for (var i = 0; i < this.size; i++) {
            var temp = new Array();
            for (var j = 0; j < this.size; j++) {
                temp.push(parseInt(Math.random() * 10));
            }
            this.data.push(temp);
        }
    }
};

async function main() {
    const start = await Date.now();
    let size = await +process.argv[2];
    matrix1 = await new Matrix(size);
    await matrix1.create();
    // await matrix1.get_data();
    matrix2 = await new Matrix(size);
    await matrix2.create();
    // await matrix2.get_data();
    await multiply(matrix1.data, matrix2.data, size);
    const stop = await Date.now();
    console.log(stop - start + ' Milisegundos');
    await rl.close();
};
main();