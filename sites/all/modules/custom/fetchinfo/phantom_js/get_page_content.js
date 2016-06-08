var url = 'http://program.gxtv.cn';
var page = require('webpage').create();

page.open(url, function() {
  console.log(page.content);
  phantom.exit();
})
