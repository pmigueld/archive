// Allows selective batch download
// Just check the images you want to download and hit the [Download Selected] button

javascript: (function() { 

if(window.jsDanbooruLoaded) { 
	alert("jsDanbooru already loaded"); return; 
}

var images = document.querySelector(".thumb"),
    sidebar = document.querySelector(".sidebar")[0],
    selection = [],
    postID = [],
    links_html = "",
    n = images.length;

function createButton(value) {
	var btn = document.createElement("input");	
	btn.type = "button";
	btn.value = value;
	return btn;
}

function makeDownloader(mode) {
	return function(e) {
		n = images.length;
		links_html = "";
		for(var i = 0; i < n; i++) {
			if(mode === "all" || selection[i].checked) {
				var imgsrc = Post.posts.get(postID[i]).sample_url;
				links_html += "<a href=" + imgsrc + ">" + imgsrc + "</a><br />\n";
			}
		}
		var links = window.open();
		links.document.write(links_html); 
		links.document.close();
	}; 
}

for(var i = 0; i < n; i++) {
	selection[i] = document.createElement("input");
	selection[i].type = "checkbox";
	images[i].appendChild(selection[i]);
	postID[i] = parseInt(images[i].parentNode.id.substring(1), 10) || 
		    parseInt(images[i].id.substring(1), 10);
}

var download_selected = createButton("Download Selected");
download_selected.onclick = makeDownloader("selected");
	
var download_all = createButton("Download All");
download_all.onclick = makeDownloader("all");

var buttons = document.createElement("center");
buttons.appendChild(download_selected);
buttons.appendChild(download_all);
sidebar.appendChild(buttons); 
window.jsDanbooruLoaded = true; 

})();  // "pmigueld\0"