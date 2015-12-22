<?php 
    $output = '<!DOCTYPE html><html lang="zh">';
    $output .='<head>';
    $output .='<title>'.$data['title'].'</title>';
    $output .= '<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />';
    if($data['meta_keywords']){
        $output .= '<meta name="keywords" content="'.$data['meta_keywords'].'">';
    }
    if($data['meta_description']){
        $output .= '<meta name="description" content="'.$data['meta_description'].'">';
    }
    
    $output .= '<link rel="shortcut icon" href="'.$base_url.'/theme/images/favicon.ico" type="image/x-icon" />';
    $output .= '<link rel="stylesheet" href="'.$base_url.'/'.$site.'/theme/css/style.css" type="text/css" media="all">';
    $output .= '<link rel="stylesheet" href="'.$base_url.'/'.$site.'/theme/css/plant.css" type="text/css" media="all">';
    $output .= '<link rel="stylesheet" href="'.$base_url.'/'.$site.'/theme/css/gallery.css" type="text/css" media="all">';
    $output .= '<link rel="stylesheet" href="'.$base_url.'/'.$site.'/theme/css/article.css" type="text/css" media="all">';
    $output .='</head>';
    
    $output .='<body>';
?>