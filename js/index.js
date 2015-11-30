$(document).ready(function() {

  var GCONST = .0000000000673;

  var planets = [];
  var ships = [];

  var levelData = [];

  var canvas = $("#canvas");

  var ctx = canvas[0].getContext("2d");

  var w = canvas.width();
  var h = canvas.height();

  var currLevel = 0;

  var clickNum = 1;

  readLevels();
  seedIntro();
  setInterval(animate, 90);

  canvas.on("click", function(event) {
    if(currLevel > 0) {
      clickX = parseInt(event.offsetX);
      clickY = parseInt(event.offsetY);

      if(clickNum == 1) {
        ships = [];
        ships.push({xPos: clickX, yPos: clickY, radius: 4, mass: 0});
        clickNum = 2;
      } else if(clickNum == 2) {
        s = ships[0];
        s.radius = 5;
        s.mass = 1000;
        s.xVel = (clickX-s.xPos)/4.0;
        s.yVel = (clickY-s.yPos)/4.0;

        //velocity cap
        var velMax=15;

        if(ships[0].xVel>velMax)
          ships[0].xVel=velMax;
        else if(ships[0].xVel<-1*velMax)
          ships[0].xVel=-1*velMax;
        if(ships[0].yVel>velMax)
          ships[0].yVel=velMax;
        else if(ships[0].yVel<-1*velMax)
          ships[0].yVel=-1*velMax;

        clickNum = 1;
      }
    }
  });

  function animate() {
    // Lets paint the canvas now
    ctx.fillStyle = "black";
    ctx.fillRect(0, 0, w, h);

    if(currLevel == 0) {
      ctx.fillStyle = "rgb(240, 220, 130)";
      ctx.font = "lighter 70px Helvetica";
      ctx.fillText("Gravity Sim v9.8", 85, 110);

      drawIntroButtons();
    }

    //draw planets
    for(var i = 0; i<planets.length; i++) {
      ctx.strokeStyle = "rgb(0, 100, 255)";
      drawBall(planets[i].xPos, planets[i].yPos, planets[i].radius);
    }

    //draw ships
    for(var i = 0; i<ships.length; i++) {
      updateShipPosition(i);
      ctx.strokeStyle = "rgb(50, 250, 30)";
      drawBall(ships[i].xPos, ships[i].yPos, ships[i].radius);
    }
  }

  //find the net force on the ship due to the planets,
  //derive and apply the acceleration to get the new velocity and thus new position
  function updateShipPosition(shipIdx) {
    var netXForce=0;
    var netYForce=0;

    // ship isn't ready to fly
    if(ships[shipIdx].mass == 0) { return }

    for(var i = 0; i<planets.length; i++) {
      var x1 = ships[shipIdx].xPos;
  		var y1 = ships[shipIdx].yPos;
  		var x2 = planets[i].xPos;
  		var y2 = planets[i].yPos;
  		var dist = Math.sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
      var gForce = 0;

      //don't add any gravitational force if the planet is within 5, as its probably about to collide anyways, and by applying such a large force,
  		//the ship will be catapulted "through" the planet to a galaxy far far away.
  		//with that being said, it does cause a slight "glitch" in that if a ship manages to pass within around
  		//5 pixels it will actually "avoid" the planet
  		//However, I prefer to think of it more as a quirk than a glitch, after all, gravity for planets and puny ships
  		//doesn't really work as strongly as we have it anyways.
  		if(dist<5.0) {
  			gForce = 0;
      } else {
  			gForce = GCONST * ships[shipIdx].mass * planets[i].mass / dist;
  		}

      //split this force into x and y components
      var theta = Math.atan((y2-y1)/(x2-x1+.01));

      //depending on the relative positioning the force will either be in the positive
      //or negative x and y directions
      if(x1>x2)
      {
        netXForce -= gForce * Math.cos(theta);
        netYForce -= gForce * Math.sin(theta);
      }
      else
      {
        netXForce += gForce * Math.cos(theta);
        netYForce += gForce * Math.sin(theta);
      }
    }

    //update position and velocity
    ships[shipIdx].xPos += ships[shipIdx].xVel+netXForce/ships[shipIdx].mass;
    ships[shipIdx].yPos += ships[shipIdx].yVel+netYForce/ships[shipIdx].mass;

    ships[shipIdx].xVel += netXForce/ships[shipIdx].mass;
    ships[shipIdx].yVel += netYForce/ships[shipIdx].mass;
  }

  function drawBall(centerX, centerY, radius) {
    ctx.beginPath();
    ctx.arc(centerX, centerY, radius, 0, 2 * Math.PI, false);
    ctx.stroke();
  }

  //buttons for the intro screen
  function drawIntroButtons() {
    if($("#arcade-button").length < 1) {
      $("#canvas-wrapper").append("<button id='arcade-button' class='gravity-button'>Arcade</button>");
      $("#arcade-button").on("click", function() {
        seedPlanets(1);
        $(".gravity-button").remove();
      });
    }

    if($("#sandbox-button").length < 1) {
      $("#canvas-wrapper").append("<button id='sandbox-button' class='gravity-button'>Sandbox</button>");
    }
  }

  function readLevels() {
    d3.csv("levels.csv", function(data) {
      levelData = data;
    });
  }

  function seedPlanets(level) {
    planets = [];
    ships = [];
    levelData.forEach(function(p){
      if(parseInt(p.level) == level) {
        planets.push(p);
      }
    });
    currLevel = level;
  }

  //seed the intro animation
  function seedIntro() {
  	//2 ships orbiting 2 planets
    p1 = {
      mass: 2000000000000,
      radius: 10,
      xPos: 260,
      yPos: 320
    };
    planets.push(p1);

    p2 = {
      mass: 2000000000000,
      radius: 10,
      xPos: 400,
      yPos: 340
    };
    planets.push(p2);

    s1 = {
      xPos: 340,
    	yPos: 200,
    	radius: 5,
    	mass: 1000,
    	xVel: 15,
    	yVel: 0
    };
    ships.push(s1);

    s2 = {
      xPos: 330,
    	yPos: 350,
    	radius: 5,
    	mass: 1000,
    	xVel: -3,
    	yVel: 20
    };
    ships.push(s2);
  }
});
