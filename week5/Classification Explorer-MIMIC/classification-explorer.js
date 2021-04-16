function ClassificationExplorer()
{
    this.TEST_SET_W = 100;
    this.TEST_SET_H = 100;
    this.output = new Array(this.TEST_SET_W * this.TEST_SET_H);
    this.colours = [
        "",
        "#0ED779",
        "#4D42EB",
        "#FFCE00",
        "#F79994",
        "#ED3D05",
        "#1EA4D9",
        "#01A8E5",
        "#D52366",
        "#01E578",
    ];

    this.recording = false;

    this.setup = (canvasName, myClassification)=> {
        this.canvasName = canvasName;
        this.myClassification = myClassification;
        this.canvas = document.getElementById(this.canvasName);
        this.context = canvas.getContext("2d");
        window.requestAnimationFrame(this.draw);
        this.canvas.addEventListener('mousemove', this.move);
        console.log(this.canvas.width, this.canvas.height)
        this.recordingClass = -1;
        this.trainingSet = [];
        window.addEventListener('keyup', this.stopRecord, false);
        window.addEventListener('keydown', this.startRecord, false);
    }

    this.move = (mousePosition)=> {
        if(this.recordingClass > 0 && this.recording)
        {
            if (mousePosition.layerX || mousePosition.layerX === 0)
            {
                this.mouseX = mousePosition.layerX;
                this.mouseY = mousePosition.layerY;
            }
            else if (mousePosition.offsetX || mousePosition.offsetX === 0)
            {
                this.mouseX = mousePosition.offsetX;
                this.mouseY = mousePosition.offsetY;
            }
            var rapidInput = [this.mouseX / this.canvas.width, this.mouseY  / this.canvas.height];
            var rapidOutput = [this.recordingClass];
            this.trainingSet.push({
                input: rapidInput,
                output: rapidOutput
            });
            //console.log(this.output);
        }
    }

    this.startRecord = (e)=> {
        if (e.keyCode > 47 && e.keyCode < 58)
        {
            this.recordingClass = e.keyCode - 48;
        }
    }

    this.stopRecord = (e)=> {
        if (e.keyCode > 47 && e.keyCode < 58)
        {
            this.recordingClass = -1;
            this.retrain();
            this.updateOutput();
        }
    }

    this.ptForIndex = (i)=> {
        return {x:i % this.TEST_SET_W, y:Math.floor(i / this.TEST_SET_H)}
    }

    this.clear = ()=> {
        this.trainingSet = [];
        this.retrain();
        this.updateOutput();
    }

    this.retrain = ()=> {
        this.myClassification.train(this.trainingSet);
    }

    this.updateOutput = ()=> {
        for(let i = 0; i < this.output.length; i++)
        {
            const pt = this.ptForIndex(i);
            const output = this.myClassification.run([pt.x / this.TEST_SET_W, pt.y / this.TEST_SET_H]);
            this.output[i] = output;
        }
    }

    this.draw = ()=> {
        this.context.clearRect(0,0, this.canvas.width, this.canvas.height);
        const fillW = this.canvas.width / this.TEST_SET_W;// 400/100
        const fillH = this.canvas.height / this.TEST_SET_H;
        for(let i = 0; i < this.output.length; i++)
        {
            const pt = this.ptForIndex(i);
            this.context.fillStyle = this.colours[this.output[i] % this.colours.length];
            this.context.fillRect(pt.x * fillW, pt.y * fillH, fillW, fillH);
        }
        //console.log(this.trainingSet.length);
        for(let i = 0; i < this.trainingSet.length; i++)
        {
            const data = this.trainingSet[i];
            //this.context.fillStyle = this.colours[data.output % this.colours.length];
            //this.context.fillRect(data.input[0] * this.canvas.width, data.input[1] * this.canvas.height, fillW, fillH);
            this.context.strokeStyle = "#FFF"
            this.context.strokeRect(data.input[0] * this.canvas.width, data.input[1] * this.canvas.height, fillW, fillH);
        }
        window.requestAnimationFrame(this.draw);
    }
}