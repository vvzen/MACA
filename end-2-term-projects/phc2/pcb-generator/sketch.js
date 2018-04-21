// taken from https://codepen.io/anon/pen/deorva


window.addEventListener('resize', resize, false);

var cellSize = 30;
var wireLength = 20;
var cutOffLength = 2;
var straightness = 5;
var grid = [];
var gridWidth, gridHeight;
var available = [];
var wires = [];

var dirs = [
	    [-1, -1], [0, -1], [1, -1],
	        [1, 0],
		    [1, 1], [0, 1], [-1 , 1],
		        [-1, 0]
			  ];

			  function Cell(x, y){
				    this.x = x;
				      this.y = y;
				        this.available = true;
			  }

function Wire(start){
	  this.cells = [];
	    this.cells.push(start);
	      this.last = findOpenDir(start.x, start.y);
}

Wire.prototype.render = function(){
	  noFill();
	    strokeWeight(cellSize/4);
	      stroke(45, 60, 60);
	        beginShape();
		  for (var i = 0; i < this.cells.length; i++){
			      var cell = this.cells[i];
			          vertex((cell.x + .5)*cellSize, (cell.y + .5)*cellSize);
				    }
		    endShape();
		      fill(0);
		        strokeWeight(cellSize/6);
			  var end = this.cells.length - 1;
			    ellipse((this.cells[0].x + .5)*cellSize, (this.cells[0].y + .5)*cellSize, cellSize*.7);
			      ellipse((this.cells[end].x + .5)*cellSize, (this.cells[end].y + .5)*cellSize, cellSize*.7);
}

Wire.prototype.generate = function(){
	  var hasSpace = true;
	    while(this.cells.length < wireLength && hasSpace){
		        var prevCell = this.cells[this.cells.length-1];
			    var tries = [0, 1, -1];
			        if (random() > .5) tries = [0, -1, 1];
				    var found = false;
				        hasSpace = false;
					    
					    while(tries.length > 0 && !found){
						          var mod = tries.splice(floor(pow(random(),straightness)*tries.length), 1)[0];
							        var index = this.last+4+mod;
								      if (index < 0) index += 8;
								            if (index > 7) index -=8
										          var dir = dirs[index];
									          
									          var x = dir[0] + prevCell.x; 
										        var y = dir[1] + prevCell.y;
											      if (x >= 0 && x < gridWidth - 1 && y >= 0 && y < gridHeight - 1){
												              var cell = grid[x][y];
													              if (cell.available && noCrossOver(index, x, y)){
															                this.cells.push(cell);
																	          cell.available = false;
																		            hasSpace = found = true;
																			              this.last = this.last+mod;
																				                if (this.last < 0) this.last += 8;
																						          if (this.last > 7) this.last -= 8;
																							          }
														            }
											          }
					      }
}

function noCrossOver(index, x, y){
	  if (index == 0) return (grid[x+1][y].available || grid[x][y+1].available);
	    if (index == 2) return (grid[x-1][y].available || grid[x][y+1].available);
	      if (index == 4) return (grid[x-1][y].available || grid[x][y-1].available);
	        if (index == 6) return (grid[x+1][y].available || grid[x][y-1].available);
		  return true;
}

function findOpenDir(x, y){
	  var checks = [0, 1, 2, 3, 4, 5, 6, 7];
	    while (checks.length > 0){
		        var index = checks.splice(floor(random()*checks.length), 1)[0];
			    var dir = dirs[index];
			        var x2 = x + dirs[0];
				    var y2 = y + dirs[1];
				        if (x2 >= 0 && x2 < gridWidth - 1 && y2 >= 0 && y2 < gridHeight - 1){
						      if (grid[x2][y2].available) return index;
						          }
					  }
	      return 0;
}

function setup(){
	  createCanvas();
	    ellipseMode(CENTER);
	      colorMode(HSB, 360, 100, 100);
	        
	        var gui = new dat.GUI();
		  gui.add(this, "cellSize", 10, 80, 1);
		    gui.add(this, "wireLength", 1, 100, 1);
		      gui.add(this, "cutOffLength", 0, 5, 1);
		        gui.add(this, "straightness", .01, 20, .01);
			  gui.add(this, "recreate");
			    
			    resize();
}

function recreate(){
	  gridWidth = ceil(width/cellSize)+1;
	    gridHeight = ceil(height/cellSize)+1;
	      grid = [];
	        available = [];
		  wires = [];
		    
		    for (var i = 0; i < gridWidth; i++){
			        grid.push([]);
				    for (var j = 0; j < gridHeight; j++){
					          var cell = new Cell(i, j);
						        grid[i][j] = cell;
							      available.push(cell);
							          }
				      }
		      
		      while(available.length > 0){
			          var cell = available[floor(random()*available.length)];
				      cell.available = false;
				          var wire = new Wire(cell);
					      wire.generate();
					          wires.push(wire);
						      for (var i = 0; i < wire.cells.length; i++){
							            available.splice(available.indexOf(wire.cells[i]), 1);
								        }
						        }
		        loop();
}

function draw(){
	  background(120, 70, 30);
	    if (grid == undefined) return;

	      for (var i = 0; i < wires.length; i++){
		          if (wires[i].cells.length > cutOffLength) wires[i].render();
			    }
	        noLoop();
}

function resize(){
	  resizeCanvas(window.innerWidth, window.innerHeight);
	    recreate();
}
