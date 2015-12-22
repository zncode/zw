<?php 
    /* 页面头部开始 */
    $output .= '<div class="header">';
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
    $gallery = $data['gallery'];
    $gallery_name = $gallery[0]['name'];
    $gallery_description = $gallery[0]['description'];
    $gallery_contents = $gallery[0]['gallery_contents'];
    
    $output .='<div class="gallery_overview_wrapper">';
        $output .= '<div class="breadcrumb">';
        $output .= $data['breadcrumbs'];
        $output .= '</div>';
        $output .= '<div class="dian"></div>';
        
        $output .= '<div class="content">';
          /* 标题描述 */
          $output .= '<div class="gallery_title">';
          $output .= $gallery_name;
          $output .= '</div>';
          $output .= '<div class="gallery_description">';
          $output .= $gallery_description;
          $output .= '</div>';
    
          $output .= '<ul>';
              if($gallery_contents){
                foreach($gallery_contents AS $gallery_content){
                  $image_thumb_path = $base_url.'/uploads/gallery/'.$gallery_content['gallery_floder_name'].'/thumb/'.$gallery_content['image_thumb_name'];
                  $image_path       = $base_url.'/uploads/gallery/'.$gallery_content['gallery_floder_name'].'/original/'.$gallery_content['image_name'];
                  
                  $image_thumb = '<a href="'.$image_path.'" target="_blank"><img src="'.$image_thumb_path.'" alt="'.$gallery_content['title'].'"/></a><br>';
                  $output .= '<li> '.$image_thumb.l($gallery_content['title'], $image_path, array('target'=>'_blank')).' </li>';
                }
              }else {
                $output .= '<li> 暂时无内容 <li>';
              }
          $output .= '</ul>';
        $output .= '</div>';
        
        $output .= '<div class="clear"></div>';
    
        //百度文章页广告
        $output .= '<div class="ad_plant_bottom"><script type="text/javascript">var cpro_id = "u1588384";</script><script src="http://cpro.baidustatic.com/cpro/ui/c.js" type="text/javascript"></script></div>';
    
    $output .= '</div>';
    /* 中间内容结束 */
?>