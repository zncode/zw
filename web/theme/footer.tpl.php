<?php 
    $output .= '<div class="clear"></div>';

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