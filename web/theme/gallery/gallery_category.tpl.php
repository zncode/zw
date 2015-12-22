<?php 
    /* 页面头部开始 */
    $output .= '<div class="front_header">';
        //logo
        $output .= '<div class="logo">'.l('<img src="'.$base_url.'/'.$site.'/theme/images/logo.png" alt="植物365" />', $base_url).'</div>';
        //菜单
        $output .= '<div class="menu">';
          $output .= '<ul>';
          foreach($data['menus'] AS $menu) {        
              $text = $menu['name'];
              $path = $menu['path'];
              $menuOutputs[] = '<li>'.l(t($text), $path).'</li>';        
          }
          krsort($menuOutputs);
          $output .= implode('', $menuOutputs);
          $output .= '</ul>';
        $output .= '</div>';
        $output .= '<div class="submenu"></div>';
    $output .= '</div>';
    $output .= '<div class="clear"></div>';
    /* 页面头部结束 */
    
    /* 中间内容开始 */
    $output .='<div class="gallery_category_wrapper">';
        $output .= '<div class="breadcrumb">';
        $output .= $data['breadcrumbs'];
        $output .= '</div>';
        $output .= '<div class="dian"></div>';

        $output .= '<div class="content">';
          $output .= '<ul>';
          if(is_array($data['gallerys']) && count($data['gallerys'])){
            foreach($data['gallerys'] AS $gallery){
              $gid = $gallery['id'];
              $piyin = $gallery['piyin'];
              $name = $gallery['name'];
              $image = $base_url.'/uploads/gallery/'.$gid.'_'.$piyin.'/default.jpg';
              $image_thumb = '<a href="'.$base_url.'/gallery/'.$gid.'" target="_blank"><img src="'.$image.'" alt="'.$name.'"/></a><br>';
              $output .= '<li> '.$image_thumb.l($name, 'gallery/'.$gid, array('target'=>'_blank')).' </li>';
            }
          }else {
            $output .= '<li> 暂时无内容 <li>';
          }
    
          $output .= '</ul>';
        $output .= '</div>';

        $output .= '<div class="clear"></div>';
    $output .= '</div>';
    /* 中间内容结束 */

?>