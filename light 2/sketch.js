
//Written by William Luk
// posts data to an Adafuit.io feed
let url='https://io.adafruit.com/api/v2/748921292/feeds/light';
var data = 0;
var counter=0;
let lightLevel=0;
let curLevel=0;
let maxLightLevel=1024;
let button=null;
let switchOn=false;
let torchImage=null;
function setup() {
  createCanvas(windowWidth,windowHeight);
  torchImage=loadImage("./img.png");
  button=document.getElementById("button");
  button.onclick=()=>switchLight();
}

function draw() {
  background("black");
  fill(0,0,width,height);
  if(counter%80==0)
  {
	  if(switchOn)
		  getData();
  }
  counter++;
  if(curLevel>lightLevel)
	  curLevel-=(curLevel-lightLevel)/10;
  else if(curLevel<lightLevel)
	  curLevel+=(lightLevel-curLevel)/10;
  image(torchImage,width/2-torchImage.width/2,height-torchImage.height);
  if(switchOn)
	  drawLight(curLevel/maxLightLevel);
}


function getData(){

  httpGet(url, 'json', function(result){
	    if(!switchOn)
	   	 return;
    		lightLevel=parseFloat(result.last_value);
  });
}
function drawLight(p){
	if(p>1)
		p=1;
	let lightHeight=height-torchImage.height-5;
	let h=lightHeight*p;
	let x=h*Math.cos(45);
	let a=0.5+0.5*p;
	let cx=width/2;
	let y=height-torchImage.height;
	noStroke(0) 
    fill("rgba(255,255,255,"+a+")");  
    beginShape() 
    vertex(cx-x-10, y-h);
    vertex(cx+x+10, y-h);
    vertex(cx+10,y);
    vertex(cx-10,y);
    endShape()
}
function switchLight(){
	switchOn=!switchOn;
	
	if(switchOn){
		button.innerText="Switch Off";
		getData();
		
	}
	else
	{
		curLevel=0;
		lightLevel=0;
		button.innerText="Switch On";
	}
}