<?php

ini_set('date.timezone','Asia/Shanghai');

define('DOCUMENT_ROOT', getcwd());

require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. 'lib' .DIRECTORY_SEPARATOR. 'bootstrap.inc';

$arg = arg();

if(empty($arg[0])){
    require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. 'lib' .DIRECTORY_SEPARATOR. 'article.inc';
    require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. 'lib' .DIRECTORY_SEPARATOR. 'gallery.inc';
    require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. 'web' .DIRECTORY_SEPARATOR. 'module' .DIRECTORY_SEPARATOR. 'index.module.inc';
    require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. 'web' .DIRECTORY_SEPARATOR. 'controller' .DIRECTORY_SEPARATOR. 'index.controller.inc';
    index();
}

if($arg[0] == 'article'){
    require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. 'lib' .DIRECTORY_SEPARATOR. 'article.inc';
    require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. 'web' .DIRECTORY_SEPARATOR. 'module' .DIRECTORY_SEPARATOR. 'article.module.inc';
    require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. 'web' .DIRECTORY_SEPARATOR. 'controller' .DIRECTORY_SEPARATOR. 'article.controller.inc';
    article_view();
}
if($arg[0] == 'article_category'){
    require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. 'lib' .DIRECTORY_SEPARATOR. 'article.inc';
    require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. 'web' .DIRECTORY_SEPARATOR. 'module' .DIRECTORY_SEPARATOR. 'article.module.inc';
    require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. 'web' .DIRECTORY_SEPARATOR. 'controller' .DIRECTORY_SEPARATOR. 'article.controller.inc';
//         article_category_view();
}

if($arg[0] == 'plant'){
    require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. 'lib' .DIRECTORY_SEPARATOR. 'plant.inc';
    require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. 'web' .DIRECTORY_SEPARATOR. 'module' .DIRECTORY_SEPARATOR. 'plant.module.inc';
    require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. 'web' .DIRECTORY_SEPARATOR. 'controller' .DIRECTORY_SEPARATOR. 'plant.controller.inc';
    plant_view();
}

if($arg[0] == 'plant_category'){
    require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. 'lib' .DIRECTORY_SEPARATOR. 'plant.inc';
    require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. 'web' .DIRECTORY_SEPARATOR. 'module' .DIRECTORY_SEPARATOR. 'plant.module.inc';
    require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. 'web' .DIRECTORY_SEPARATOR. 'controller' .DIRECTORY_SEPARATOR. 'plant.controller.inc';
    plant_category_view();
}

if($arg[0] == 'gallery'){
    require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. 'lib' .DIRECTORY_SEPARATOR. 'gallery.inc';
    require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. 'web' .DIRECTORY_SEPARATOR. 'module' .DIRECTORY_SEPARATOR. 'gallery.module.inc';
    require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. 'web' .DIRECTORY_SEPARATOR. 'controller' .DIRECTORY_SEPARATOR. 'gallery.controller.inc';
    gallery_view();
}

if($arg[0] == 'gallery_category'){
    require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. 'lib' .DIRECTORY_SEPARATOR. 'gallery.inc';
    require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. 'web' .DIRECTORY_SEPARATOR. 'module' .DIRECTORY_SEPARATOR. 'gallery.module.inc';
    require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. 'web' .DIRECTORY_SEPARATOR. 'controller' .DIRECTORY_SEPARATOR. 'gallery.controller.inc';
    gallery_category_view();
}

if($arg[0] == 'pagenotfound'){
    page_not_found();
}

?>