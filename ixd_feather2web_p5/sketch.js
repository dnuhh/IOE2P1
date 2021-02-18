let url = 'https://io.adafruit.com/api/v2/dnuh/feeds/button';
let counter = 0;

function setup() {
    createCanvas(windowWidth, windowHeight);
    colorMode(HSB);
    text('Font Size 20', 10, 90);
}

function draw() {
//    fill(255, 10);
    
    ellipse(200, 200, 100,100);
    if (counter % 80 == 0) {
        getData();
    }
    counter++;
}

function getData() {
    let data, username, name;
    httpGet(url, 'json', function (response) {
        console.log(response);
        data = response.last_value;
        username = response.username;
        if (username=="dnuh"){
            name = "Deanna";
        }
        noStroke();

        console.log("Data: "+data);
        fill(data,100,50);
        background(0,0,255);
        text(name, 100,(height/2)-20);
        
        if (data < 40){
            
            text("sad", 100,height/2);
            console.log("sad");
        }else if ((data >= 40) && (data < 80)){
            text("neutral", 100,height/2);
            console.log("neutral");
        }else{
            text("happy", 100,height/2);
            console.log("happy");
        }
    });
}
