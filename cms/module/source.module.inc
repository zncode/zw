<?php

/**
 * 文章资源页面
 */
function source_get_articles(){
    $output ='';

    $articles['quwei'][]  = array('植物通'=>'http://www.zhiwutong.com/learning/interest.htm');
    $articles['quwei'][]  = array('那花园'=>'http://www.nahuayuan.com/baike/changshi/');
    $articles['quwei'][]  = array('中国风景园林网'=>'http://www.chla.com.cn/cat/c11/zhiwukepu/quweizhiwu/');
    $articles['quwei'][]  = array('植物网一站搞定-资讯'=>'http://www.zhiwuwang.com/news/');

    $articles['xinwen'][] = array('中国植物科学门户平台'=>'http://www.chinaplant.org');

    $articles['kexue'][]  = array('植物通'=>'http://www.zhiwutong.com/news/keji.htm');

    $articles['zhizui'][] = array('度哥世界之最'=>'http://www.dugoogle.com/tag/%E6%A4%8D%E7%89%A9%E4%B9%8B%E6%9C%80/');
    $articles['zhizui'][] = array('植物网'=>'http://www.zhw0.com/_d274265236.htm');

    $articles['zhishi'][] = array('植物通'=>'http://www.zhiwutong.com/learning/knowledge.htm');

    $articles['lishi'][]  = array('植物网'=>'http://www.zhw0.com/_d274246692.htm');

    $articles['gushi'][]  = array('植物网'=>'http://www.zhw0.com/_d274265105.htm');

    $articles['baohu'][]  = array('植物通'=>'http://www.zhiwutong.com/learning/rare.htm');

    $articles['xuejia'][] = array('植物通'=>'http://www.zhiwutong.com/science/botanist.htm');

    $articles['mingci'][] = array('植物通'=>'http://www.zhiwutong.com/learning/mingci.htm');

    $articles['meiri'][] = array('植物吧'=>'http://tieba.baidu.com/f?kw=%E6%A4%8D%E7%89%A9&ie=utf-8');
    $articles['meiri'][] = array('花吧'=>'http://tieba.baidu.com/f?kw=%E8%8A%B1&ie=utf-8');
    $articles['meiri'][] = array('多肉吧'=>'http://tieba.baidu.com/f?kw=%E5%A4%9A%E8%82%89&ie=utf-8');

    $articles['geyan'][] = array('格言网'=>'http://www.geyanw.com/');

    $i = 1;
    foreach($articles AS $category_name => $article){
        $output .= $i.'.'.source_get_category_name($category_name).'<ul>';
        foreach($article AS $value){
            foreach($value AS $a => $b){
                $output .= '<li>'.$a.'&nbsp;'.l('>>', $b, array('target'=>'_blank')).'</li>';
            }
        }
        $output .= '</ul>';
        $i++;
    }

    return $output;
}

/**
 * 植物网站
 */
function source_get_plants(){
    $srouces[] = array('http://www.zhiwuwang.com'=>'植物网_与植物相关一站搞定');
    $srouces[] = array('http://www.zhiwutong.com'=>'植物通');
    $srouces[] = array('http://www.plantphoto.cn'=>'PPBC中国植物图像库——最大的植物分类图片库');
    $srouces[] = array('http://www.zhw0.com'=>'植物网');
    $srouces[] = array('http://www.huatan.net/bbs'=>'花谈');
    $srouces[] = array('http://www.tahua.net/'=>'踏花行');
    $srouces[] = array('http://www.yuhuagu.com/'=>'浴花谷');
    $srouces[] = array('http://www.bioon.com/popular/plant/Index.shtml'=>'植物世界-科普-生物谷');
    $srouces[] = array('http://www.eflora.cn'=>'eFlora 中国在线植物志');
    $srouces[] = array('http://frps.eflora.cn/'=>'FRPS《中国植物志》全文电子版网站');
    $srouces[] = array('http://www.chla.com.cn/'=>'风景园林网');
    $srouces[] = array('http://frps.eflora.cn/'=>'FRPS《中国植物志》全文电子版网站');
    $srouces[] = array('http://blog.sina.com.cn/ermufossil'=>'二木的花园');
    $srouces[] = array('http://blog.sina.com.cn/boyunle'=>'博耘的博客');
    $srouces[] = array('http://tieba.baidu.com/f?ie=utf-8&kw=%E6%A4%8D%E7%89%A9'=>'植物吧');
    $srouces[] = array('http://tieba.baidu.com/f?ie=utf-8&kw=%E9%A3%9F%E8%99%AB%E6%A4%8D%E7%89%A9'=>'食虫植物吧');
    $srouces[] = array('http://www.chinese-cp.com/index.php'=>'中国食虫植物网');
    $srouces[] = array('http://shichongzhiwu.com/'=>'食虫植物网');
    $srouces[] = array('http://www.nahuayuan.com'=>'那花园');
    $srouces[] = array('http://www.dugoogle.com/tag/%E6%A4%8D%E7%89%A9%E4%B9%8B%E6%9C%80/'=>'植物之最');
    $srouces[] = array('http://www.kepu.net.cn/gb/lives/plant/knowledge/most/kwg01.html'=>'植物之最_中国科普博览');
    $srouces[] = array('http://www.zw3w.com'=>'植物百科');
    $srouces[] = array('http://www.chinaplant.org'=>'中国植物科学门户平台');


    $srouces1[] = array('http://tieba.baidu.com/p/2789742813'=>'那些花儿');
    $srouces1[] = array('http://tieba.baidu.com/p/808537208'=>'【植物大观园】中国药用植物集');
    $srouces1[] = array('http://tieba.baidu.com/p/808524041'=>'【植物大观园】园林植物集');
    $srouces1[] = array('http://tieba.baidu.com/p/2410511146'=>'请认认奇花异草');
    $srouces1[] = array('http://tieba.baidu.com/p/2338874831'=>'常见多肉植物の150张精美图鉴');
    $srouces1[] = array('http://pp.fengniao.com/album_27.html'=>'花卉摄影作品,花卉摄影图片,生态摄影-蜂鸟相册');
    $srouces1[] = array('http://yc62093801.blog.163.com/blog/static/50748202201147103230562'=>'世界十大奇异植物');
    $srouces1[] = array('http://tieba.baidu.com/p/2459479521'=>'有没有喜欢花草树木同时喜欢随手街拍的朋友，走起。。。');

    $output = '';
    $i = 1;
    foreach($srouces AS $srouce){
        $path = array_keys($srouce);
        $path = $path[0];
        $title = array_values($srouce);
        $title = $title[0];
        $output .= $i.'. '.$title.'&nbsp;'.l('>>', $path, array('target'=>'_blank'));
        $output .= '<br>';
        $i++;
    }

    $output .= '<br>';
    $output .= '<br>';
    $output .= '<br>';

    $j = 1;
    foreach($srouces1 AS $srouce){
        $path = array_keys($srouce);
        $path = $path[0];
        $title = array_values($srouce);
        $title = $title[0];
        $output .= $j.'. '.$title.'&nbsp;'.l('>>', $path, array('target'=>'_blank'));
        $output .= '<br>';
        $j++;
    }

    return $output;
}

/**
 * 获取目录名称
 * @param unknown $category_name
 * @return string
 */
function source_get_category_name($category_name){

  switch($category_name){
    case 'quwei';
      $name = '趣味植物';
      break;
    case 'xinwen';
      $name = '植物新闻';
      break;
    case 'kexue';
      $name = '植物科学';
      break;
    case 'zhizui';
      $name = '植物之最';
      break;
    case 'zhishi';
      $name = '植物知识';
      break;
    case 'lishi';
      $name = '植物历史';
      break;
    case 'gushi';
      $name = '植物故事';
      break;
    case 'baohu';
      $name = '植物保护';
      break;
    case 'xuejia';
      $name = '植物学家';
      break;
    case 'mingci';
      $name = '植物名词';
      break;
    case 'meiri';
      $name = '每日养眼';
      break;
    case 'geyan';
      $name = '名人名言 人生格言';
      break;
  }

  return $name;
}

?>