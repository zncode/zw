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
    $output .='<div class="plant_overview_wrapper">';
        $output .= '<div class="breadcrumb">';
        $output .= $data['breadcrumbs'];
        $output .= '</div>';
        $output .= '<div class="dian"></div>';
        

        $output .= '<div class="content">';
            $output .= '<ul>';
            if($data['plants']){
              foreach($data['plants'] AS $cid => $plant){
                $link_url    = PLANT_BASE_PATH.'/'.$cid;
                $path        = $plant[0]['images']['thumbnail'];
                $image_thumb = l('<img src="'.$path.'" alt="'.$plant[0]['name'].'" />', $link_url).'<br>';
    
                $output .= '<li> '.$image_thumb.l($plant[0]['name'], $link_url).' </li>';
              }
            }else {
              $output .= '<li> 暂时无内容 <li>';
            }
            $output .= '</ul>';
        $output .= '</div>';

        $output .= '<div class="clear"></div>';
        $output .= $data['pager'];
    $output .= '</div>';
    /* 中间内容结束 */

?>