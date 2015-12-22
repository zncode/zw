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
    $output .='<div class="plant_detail_wrapper">';
        $output .= '<div class="breadcrumb">';
        $output .= $data['breadcrumbs'];
        $output .= '</div>';
        $output .= '<div class="dian"></div>';
        
        $output .='<div class="content">';
        
        $output .='<div class="tree_content_wrapper">';
        if($data['plant_content']){
          $name = $data['plant']['name'];
          $content = html_content($data['plant_content']['content']);
        
          $output .='<div class="title"><h1>'.$name.'</h1></div>';
          $output .='<div class="text">';
          $output .= $content;
          $output .= '</div>';
        
        }else {
          $output .= '<div class="text"> 暂无内容 </div>';
        }
        $output .= '</div>';
        
        /* photo gallery */
        $output .='<div class="tree_gallery_wrapper">';
        $images             = $data['plant']['images'];
        $images_thumbs      = $images['thumbs'];
        $images_originals   = $images['originals'];
        
        $output .= '<ul>';
        if(is_array($images_thumbs) && count($images_thumbs)) {
        
          foreach($images_thumbs AS $key => $images_thumb){
            $output .= '<li>';
            $output .= '<a href="'.$images_originals[$key].'" target="_blank"><img src="'.$images_thumb.'" alt="'.$name.'" /></a>';
            $output .= '</li>';
          }
        }else{
          $output .= '暂无图片';
        }
        $output .= '</ul>';
        $output .= '</div>';
        
        $output .= '<div class="clear"></div>';
    
        //百度文章页广告
        $output .= '<div class="ad_plant_bottom"><script type="text/javascript">var cpro_id = "u1588384";</script><script src="http://cpro.baidustatic.com/cpro/ui/c.js" type="text/javascript"></script></div>';
    
    $output .= '</div>';
    /* 中间内容结束 */
?>