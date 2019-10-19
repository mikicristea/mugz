let photos = document.querySelectorAll(".card");
photos.forEach( function(e){
  // let aString="url(\'""background-image:"+ e.dataset.url+"\')";
  e.setAttribute("style", "background-image:url("+e.dataset.url+")");
  console.log("url("+e.dataset.url+")");
  console.log(e.children);
  e.children[0].textContent=e.dataset.name;
});

$( document ).ready(function() {
  $('.modal').modal('hide');

  $('.card').on("click",function(){

    $( ".modal" ).modal('show');
    $('.modal-title').text(this.dataset.name);
    $('.modal-image').attr('src',this.dataset.url);
    $('.modal-text').text(this.dataset.description);
  });

});
