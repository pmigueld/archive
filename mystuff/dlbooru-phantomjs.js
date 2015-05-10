var page = new WebPage();

var url = "http://danbooru.donmai.us/post/?limit=1000&tags=";
var artist = phantom.args[0];

page.open(url + artist, function (status) {
    if (status !== "success") {
        console.log("Unable to access network.");
    } else {
        var data = page.evaluate(function () {
            var images = document.querySelectorAll(".thumb"),
                n      = images.length,
                links  = [];

            for(var i = 0; i < n; i++) {
                postID = parseInt( (images[i].id || images[i].parentNode.id).substring(1), 10 );
                // change to '.file_url' for full resolution images
                imgsrc = Post.posts.get(postID).sample_url;
                links.push(imgsrc);
            }
            return links.join("\n");
        });
        console.log(data);
    }
    phantom.exit();
});

