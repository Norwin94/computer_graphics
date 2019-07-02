var canvas = document.getElementById("glcanvas");
var ctx = canvas.getContext("2d");
 if(!ctx) {
	 ctx = canvas.getContext("experimental-webgl");
 }
  if(!ctx) {
	 ctx = canvas.getContext("webgl");
 }
  if(!ctx) {
	 alert("Not supportive");
 }
 var szerokosc = 1000;
 var wysokosc = 866;
 var poziom = 1;
 var x1 = 0;
 var y1 = 0;
 var randek = 10;
 
 var najwyzszyPoziom = 6;
 
 var my_gradient = ctx.createLinearGradient(0, 0, 1000, 0);
	for (step = 0; step < 11; step++) {
		var i = step*0.1;
		my_gradient.addColorStop(i, "#"+((1<<24)*Math.random()|0).toString(16));
	}
	
	drawTraingles(x1,y1,szerokosc,wysokosc, poziom);
	//drawTraingles(0,0,1000,866, 2);



  function action()
	{
		ctx.clearRect(0, 0, 1000, 866);
		var newCanvas = document.getElementById("glcanvas");
		var newCtx = newCanvas.getContext("2d");
		clearCanvasGrid("glcanvas");
		//ctx.clear();
		najwyzszyPoziom = document.getElementById("numberDivision").value;
		drawTraingles(x1,y1,szerokosc,wysokosc, poziom);
		//window.location.reload();
		//
	}  
	function action1()
	{
		ctx.clearRect(0, 0, 1000, 866);
		var newCanvas = document.getElementById("glcanvas");
		var newCtx = newCanvas.getContext("2d");
		clearCanvasGrid("glcanvas");
		//ctx.clear();
		randek = document.getElementById("numberPerturbance").value;
		drawTraingles(x1,y1,szerokosc,wysokosc, poziom);
		//window.location.reload();
		//
	}

 function drawTraingles(iks, igrek, szer, wys, ktoryPoziom)
 {
    var width = szer;
	var high = wys;
	var xP = iks;
	var yP = igrek;
	var level = Math.pow(2,ktoryPoziom);
	
	width /=level; 
	high /=level;
	
	var nextX1 = xP;
	var nextY1 = yP;
	
	var nextX2 = xP + width;
	var nextY2 = yP;
	
	var nextX3 = (xP + width)/2 + xP/2;
	var nextY3 = yP + high
	 
	
	ctx.beginPath();

	if(ktoryPoziom == najwyzszyPoziom)
	{
	ctx.fillStyle = my_gradient
    ctx.moveTo(xP + Math.random() * randek,yP+ Math.random() * randek);								
    ctx.lineTo(xP + width+ Math.random() * randek, yP+ Math.random() * randek); 	    									
    ctx.lineTo(xP + (width)/2 + Math.random() * randek, yP + high + Math.random() * randek);
	ctx.fill();
	
	
	ctx.moveTo(xP + width + Math.random() * randek, yP + Math.random() * randek);		
    ctx.lineTo(xP + width + width + Math.random() * randek,yP + Math.random() * randek); //						
    ctx.lineTo((xP + width + width/2 + Math.random() * randek), yP + high + Math.random() * randek)//							   
	ctx.fill();
   
	
	ctx.moveTo((xP + width)/2 + xP/2 + Math.random() * randek, yP + high + Math.random() * randek);
    ctx.lineTo((xP + width + width/2 + Math.random() * randek), yP + high + Math.random() * randek)						   
    ctx.lineTo((xP + width)+ Math.random() * randek, (yP + high + high)+ Math.random() * randek)      //	
	ctx.fill();
	}
	else {
		ktoryPoziom++;
		drawTraingles(nextX1,nextY1,szerokosc,wysokosc, ktoryPoziom);
		drawTraingles(nextX2,nextY2,szerokosc,wysokosc, ktoryPoziom);
		drawTraingles(nextX3,nextY3,szerokosc,wysokosc, ktoryPoziom);}
	
 }
 
 function clearCanvasGrid(canvasID){
    canvas = document.getElementById(canvasID); //because we are looping //each location has its own canvas ID
    context = canvas.getContext('2d');
    context.beginPath();

    // Store the current transformation matrix
    context.save();

    // Use the identity matrix while clearing the canvas
    context.setTransform(1, 0, 0, 1, 0, 0);
    context.clearRect(0, 0, canvas.width, canvas.height);

    // Restore the transform
    context.restore(); //CLEARS THE SPECIFIC CANVAS COMPLETELY FOR NEW DRAWING
}
 










