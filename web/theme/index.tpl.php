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
    $output .= '<div class="frontpage_left_content">';
    $output .= '<ul>';
    if(is_array($data['articles']) && count($data['articles'])) {
        foreach($data['articles'] AS $article){
            $output .= '<li>';
            $teaser = html_content($article['teaser']);
            $output .= '<div class="blog_title">'.l($article['title'], 'article/'.$article['id'], array('target'=>'_blank')).'</div>';
            $output .= '<div class="blog_date">'.date('Y-m-d', trim($article['created'])).'</div>';
            $output .= '<div class="blog_teaser">'.$teaser.'</div>';
            $output .= '</li>';
        }
    }else {
        $output .= '<li>';
        $output .= '<div class="blog_title">也谈WIN8 RTM的发布也谈WIN8 RTM的发布</div>';
        $output .= '<div class="blog_date">2012-8-13 &nbsp;&nbsp;&nbsp;&nbsp;</div>';
        $output .= '<div class="blog_teaser">以期在正式发布时候实现软硬件的兼容，这标志着Windows 8的代码开发工作已经完成。未来几周，制造商就可以将Windows 8安装到电脑中，并于10月26日推出。微软近日宣布，Windows 8操作系统已经正式向硬件制造商发布RTM版本，并提交给了硬件厂商研发硬件，以期在正式发布时候实现软硬件的兼容，这标志着Windows 8的代码开发工作已经完成。未来几周，制造商就可以将Windows 8安装到电脑中，并于10月26日推出。微软近日宣布，Windows 8操作系统已经正式向硬件制造商发布RTM版本，并提交给了硬件厂商研发硬件，以期在正式发布时候实现软硬件的兼容，这标志着Windows 8的代码开发工作已经完成。未来几周，制造商就可以将Windows 8安装到电脑中，并于10月26日推出。</div>';
        $output .= '</li>';
    
        $output .= '<li>';
        $output .= '<div class="blog_title">也谈WIN8 RTM的发布也谈WIN8 RTM的发布</div>';
        $output .= '<div class="blog_date">2012-8-13 &nbsp;&nbsp;&nbsp;&nbsp;</div>';
        $output .= '<div class="blog_teaser">以期在正式发布时候实现软硬件的兼容，这标志着Windows 8的代码开发工作已经完成。未来几周，制造商就可以将Windows 8安装到电脑中，并于10月26日推出。微软近日宣布，Windows 8操作系统已经正式向硬件制造商发布RTM版本，并提交给了硬件厂商研发硬件，以期在正式发布时候实现软硬件的兼容，这标志着Windows 8的代码开发工作已经完成。未来几周，制造商就可以将Windows 8安装到电脑中，并于10月26日推出。微软近日宣布，Windows 8操作系统已经正式向硬件制造商发布RTM版本，并提交给了硬件厂商研发硬件，以期在正式发布时候实现软硬件的兼容，这标志着Windows 8的代码开发工作已经完成。未来几周，制造商就可以将Windows 8安装到电脑中，并于10月26日推出。</div>';
        $output .= '</li>';
    }
    $output .= '</ul>';
    
    // add pager
    if($data['pager']) {
        $output .= $data['pager'];
    }
    //首页百度广告
    $output .= '<br><br><div class="ad_front_bottom"><script type="text/javascript">var cpro_id = "u1587014";</script><script src="http://cpro.baidustatic.com/cpro/ui/c.js" type="text/javascript"></script></div>';
    $output .= '</div>';
    
    $output .= '<div class="frontpage_right_content">';

   //右侧内容
    $output .= '<ul>';
    $i = 0;
    foreach($data['gallerys'] AS $gallery){
      if($i < 10){
        $gid            = $gallery['id'];
        $gallery_name   = $gallery['name'];
        $default_pic    = $gallery['default_pic'];

        $output .= '<li>';
          $output .= '<div class="picture_picture">'.l('<img src="'.$default_pic.'" alt="'.$gallery_name.'" />', 'gallery/'.$gid).'</div>';
          $output .= '<div class="picture_title">'.l($gallery_name, 'gallery/'.$gid).'</div>';
        $output .= '</li>';
      }else{
        break;
      }
      $i++;
    }
    $output .= '</ul>';
    $output .= '<div>>>'.l('查看更多', 'gallery_category').'</div>';
    $output .= '</div>';
    $output .= '<div class="clear"> </div>';
    /* 中间内容结束 */
    
    /* 底部内容开始 */
    $output .= '<div class="footer">';
    $output .= '<br> &copy; 2012 www.zhiwu365.com 植物365 京ICP备09036132号-4';
    $output .= '<br><br> 信息来源于网络，服务于网民，旨在传播植物科普知识。网站中转载的资料及图片，其版权属原作者或页面内声明的版权人拥有。 站长邮箱: zhiwu365@163.com';
    $output .= '</div>';
    
    //友情链接
    $output .= '<div class="friendlinks">';
    $output .= '<ul>';
    $output .= '<li><b>友情链接:</b></li>';
    foreach($data['friendlinks'] AS $url => $name){
        $output .= '<li><a href="'.$url.'" target="_blank" title="'.$name.'">'.$name.'</a></li>';
    }
    $output .= '</ul>';
    $output .= '</div>';
    
    //百度统计
    $output .= '<div class="tongji">';
    $output .= '<script type="text/javascript">
        var _bdhmProtocol = (("https:" == document.location.protocol) ? " https://" : " http://");
        document.write(unescape("%3Cscript src=\'" + _bdhmProtocol + "hm.baidu.com/h.js%3Fd425079352a087acf726a6d3a609ca25\' type=\'text/javascript\'%3E%3C/script%3E"));
        </script>
        ';
    $output .= '</div>';
    
    /* 底部内容结束 */
    
    $output .='</body>';
    $output .='</html>';

?>