<?php 
    global $base_url;
    
    $output = '<!DOCTYPE html><html lang="zh">';
    $output .='<head>';
    $output .='<title>'.$data['title'].'</title>';
    $output .= '<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />';
    $output .= '<meta name="keywords" content="页面没有找到">';
    $output .= '<meta name="description" content="页面没有找到">';
    
    $output .= '<link rel="shortcut icon" href="'.$base_url.'/web/theme/images/favicon.ico" type="image/x-icon" />';
    $output .= '<link rel="stylesheet" href="'.$base_url.'/web/theme/css/style.css" type="text/css" media="all">';
    $output .='</head>';
    
    $output .='<body>';
    
    /* 页面头部开始 */
    $output .= '<div class="header">';
        //logo
        $output .= '<div class="logo">'.l('<img src="'.$base_url.'/web/theme/images/logo.png" alt="植物365" />', $base_url).'</div>';
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
    $output .= '<script type="text/javascript">
    function isIFrameSelf(){try{if(window.top ==window){return false;}else{return true;}}catch(e){return true;}}
    function toHome(){ if(!isIFrameSelf()){ window.location.href="'.$base_url.'";}}
    window.setTimeout("toHome()",5000);</script>';


     $output .= '<div class="main"><br><h3>页面没有找到 5 秒钟之后将会带您进入首页!</h3></div>';
    /* 中间内容结束 */
    
    /* 底部内容开始 */
    $output .= '<div class="footer">';
    $output .= '<br> &copy; 2012 www.zhiwu365.com 植物365 京ICP备09036132号-4';
    $output .= '<br><br> 信息来源于网络，服务于网民，旨在传播植物科普知识。网站中转载的资料及图片，其版权属原作者或页面内声明的版权人拥有。 站长邮箱: zhiwu365@163.com';
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