$(function() {

	//retrait du formulaire de la page de login
	$("#login").css('display', 'none');

	// Clic sur bouton fait apparaitre le formulaire
	$("#loginseconnecter").on('click', function() {
		$("#login").css('display', 'block');
		$("#loginseconnecter").css('display', 'none');
	});	
	
	var hostname =window.location.hostname;
	var pathname =window.location.pathname;
	lien='';
	
	switch(hostname) {
		case 'cours.univ-reims.fr':
			if(pathname.startsWith('/pre-prod/', 0)) {lien="https://cours.univ-reims.fr/pre-prod";}
			else {lien="https://cours.univ-reims.fr";}
		break;
		case 'examens.univ-reims.fr':
			lien="https://examens.univ-reims.fr";
		break;
		default:
			lien='';
		break;	
	}
	
	//retrait du lien Inscrire des étudiants inséré par le plugin local/cohortenrol/edit (ajouter par plugin menu gauche)
	$("list-group-item list-group-item-action a:contains('Inscrire des étudiants').list-group-item.list-group-item-action").css('display', 'none');
	
	$("span.logo.d-none.d-sm-inline").html('<img src="'+lien+'/frontpageinsert/logo.png" alt="URCA">');
	
	// page création cours: activation popup Inscrire des étudiants 
	var page = window.location.href;
	
	// var coursepage = page.search("course/view.php");
	var position = page.indexOf("&newcourse=1"); 
	//if(coursepage != -1) {
	if(position != -1) {
		var id='';
		var fin = page.split('?');
		var parts = fin[1].split('&');
		var part0='';
		var part1='';
		
		if (parts.length>1) {
			part0= parts[0].split('=');
			part1= parts[1].split('=');
			id=part0[1];
			if(part1[0]=='newcourse') 
			{	
				if (confirm("Voulez vous inscrire des étudiants maintenant ?")) {
					// Clic sur OK
					window.location.href = "../local/cohortenrol/edit.php?courseid="+id;
				}
			}
		}
	}	
});