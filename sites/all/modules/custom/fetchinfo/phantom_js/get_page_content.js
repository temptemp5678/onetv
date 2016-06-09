var url = 'http://program.gxtv.cn';
var page = require('webpage').create();

page.open(url, function() {
  // get page content
  // var pageContent = page.content;
  // console.log(pageContent);

  // write string content to file
  var fs = require('fs');
  var filePath = 'output.txt';

  if (fs.isWritable(filePath)) {
    console.log('"' + filePath + '" is writable.');

    var content = 'Hello World!';
    fs.write(filePath, content, 'w');
  }
  else {
    console.log('"' + filePath + '" is NOT writable.');
  }

  phantom.exit();
})
