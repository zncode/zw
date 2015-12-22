<?php
define('METATAGS_DATA_PATH', DOCUMENT_ROOT.OS_SLASH.'metatags'.OS_SLASH);
define('METATAGS_INDEX', DOCUMENT_ROOT.OS_SLASH.'metatags'.OS_SLASH.'metatags.index');

/**
 * 清理页面浮动
 */
function page_clear(){
  return '<div class="clear"> </div>';
}

/**
 * 底边横线
 */
function page_dian(){
  return $output = '<div class="dian"></div>';
}

/**
 * 设置页面标题
 */
function page_set_title($title, $sitename = false){
  global $page_title, $site_name;
  $page_title = $title;
  if($sitename){
    $page_title = $page_title.'_'.$site_name;
  }
}

/**
 * 设置meta数据
 */
function page_set_metadata($meta = array()){
  global $meta_keywords, $meta_description;
  if($meta['keywords']){
    $meta_keywords = $meta['keywords'];
  }

  if($meta['description']){
    $meta_description = $meta['description'];
  }
}

/**
 * 设置meta数据
 */
function page_set_metadata_path(){
  global $meta_keywords, $meta_description;

  $arg = arg();
  $categorys = category_get_info();

  if($arg[0] == 'plant_category'){
    $category_id = $arg[1];
    foreach($categorys AS $cid => $category){
      if($category_id == $cid){
        $meta_keywords = $category['keywords'];
        $meta_description = $category['descriptions'];
      }
    }
  }else{
    $path = $arg[0];
    foreach($categorys AS $cid => $category){
      if($path == $category['path']){
        $meta_keywords = $category['keywords'];
        $meta_description = $category['descriptions'];
      }
    }
  }
}

function page_article_301(){
  global $base_url;
  $aid = arg();
  $aid = $aid[2];
  $url = $base_url.'/article/'.$aid;
  header("HTTP/1.1 301 Moved Permanently");
  header("Location: $url");
  exit();
}

function page_tree_301(){
  global $base_url;
  $arg = arg();
  $nid = $arg[2];
  if($arg[0] == 'treelist'){
    $pager_id = $arg[2];
     $url = $base_url.'/plant?pager='.$pager_id;
  }else{
    if(is_numeric($arg[1])){
      $url = $base_url.'/plant/'.$nid;
    }else{
      $url = $base_url.'/plant';
    }
  }

  header("HTTP/1.1 301 Moved Permanently");
  header("Location: $url");
  exit();
}

function temp_links(){
  $links[] = 'http://www.zhiwu365.com/article/1/52';
  $links[] = 'http://www.zhiwu365.com/article/1/56';
  $links[] = 'http://www.zhiwu365.com/article/1/50';
  $links[] = 'http://www.zhiwu365.com/article/1/1';
  $links[] = 'http://www.zhiwu365.com/article/1/48';
  $links[] = 'http://www.zhiwu365.com/article/1/49';
  $links[] = 'http://www.zhiwu365.com/article/1/3';
  $links[] = 'http://www.zhiwu365.com/article/1/2';
  $links[] = 'http://www.zhiwu365.com/article/1/23';
  $links[] = 'http://www.zhiwu365.com/article/1/32';
  $links[] = 'http://www.zhiwu365.com/article/1/52';
  $links[] = 'http://www.zhiwu365.com/article/1/52';

  return $links;
}

/**
 * 首页获取菜单
 * @return multitype:
 */
function page_get_menu(){
    $menus = array();

    /* 全站菜单以及对应路径数组 */
    $taxonomys = taxonomy_vid_load(1);

    foreach($taxonomys as $key => $taxonomy){
        $menus[$key]['name']    = $taxonomy['name'];
        $menus[$key]['path']    = 'plant_category/'.$taxonomy['tid'];
        $menus[$key]['weight']  = $taxonomy['weight'];
    }

    return $menus;
}

/**
 * 判断是否是网站首页
 */
function page_is_front($arg=NULL){
  if(!$arg){
    $arg = arg();
  }

  if(!$arg[0]){
    return true;
  }
  return false;
}

/**
 * 显示网站全部页面
 */
class Page {
  /**
   * css 包含文件
   */
  public $style = NULL;

  /**
   * Javescript 包含文件
   */
  public $js = NULL;

  /**
   * 页面标题
   */
  public $title = NULL;

  /**
   * 页面内容
   */
  public $content = NULL;

  /**
   * 页面导航条
   */
  public $breadcrumbs = NULL;

  /**
   * 页面关键字
   */
  public $meta_keywords = NULL;

  /**
   * 页面描述
   */
  public $meta_description = NULL;

  /**
   * 菜单
   */
  public $menu = NULL;

  /**
   * 网站Logo
   */
  public $logo = NULL;

  /**
   * 当前页面参数?q=的路径
   */
  public $path = NULL;

  /**
   * 分页
   */
  public $pager = false;

  /**
   * 友情链接
   */
  public $friendlinks = NULL;

  /**
   * 页面没有找到
   */
  public $pagenotfound = false;

  /**
   * 初始化所需变量
   */
  public function __construct(){
    $this->path = request_path();
    $this->breadcrumbs = array(l(t('首页'), NULL));
  }

  /**
   * 设置属性值
   */
  public function __set($name, $value){
    $this->$name = $value;
  }

  /**
   * 设置页面标题
   */
  public function SetTitle($title){
    $this->title = $title;
  }

  /**
   * 设置页面关键字
   */
  public function SetMetaKeywords($keywords){
    $this->meta_keywords = $keywords;
  }

  /**
   * 设置页面描述
   */
  public function SetMetaDescription($description){
    $this->meta_description = $description;
  }

  /**
   * 设置分页
   */
  public function SetPager($value){
    $this->pager = $value;
  }

  /**
   * 设置导航条
   */
  public function SetBreadcrumb($options){
    $breadcrumbNews = $this->breadcrumbs;

    if(is_array($options) && count($options)){
      foreach($options AS $option){
        foreach($option AS $path => $title){
          if($path != 'title'){
            $breadcrumbNews[] = l(t($title), $path);
          }else{
            $breadcrumbNews[] = $title;
          }
        }
      }
    }
    $this->breadcrumbs = $breadcrumbNews;
  }

  /**
   * 设置网站首页下方的友情链接.
   */
  public function SetFriendlinks($friendlinks){
    if(is_array($friendlinks) && count($friendlinks)){
      $output = '<div class="friendlinks">';
        $output .= '<ul>';
          $output .= '<li><b>友情链接:</b></li>';
        foreach($friendlinks AS $url => $name){
          $output .= '<li><a href="'.$url.'" target="_blank" title="'.$name.'">'.$name.'</a></li>';
        }
        $output .= '</ul>';
      $output .= '</div>';

      $this->friendlinks = $output;
    }else{
      $this->friendlinks = NULL;
    }
  }

  /**
   * 设置当前页面访问的URL
   */
  public function SetPagenotfound($a){
    $this->pagenotfound = $a;
  }
  
  /**
   * 设置当前页面访问的URL
   */
  public function SetTaxonomy($a){
      $this->taxonomy = $a;
  }
  
  /**
   * 显示页面
   */
  public function DisplayPage(){
    echo '<!DOCTYPE html><html lang="zh">';
    echo '<head>';
    $this->DisplayTitle();

    $this->DisplayMeta();
    $this->DisplayStyles();
    echo '</head>';
    echo '<body>';
    if($this->pagenotfound){
      $this->DisplayPageNotFound();
    }else{
      $this->DisplayHeader();
      if(empty($this->path) || $this->path =='front' || $this->path== 'index') {
        $this->DisplayFrontContent();
      }else{
        $this->DisplayContent();
      }

      $this->DisplayPageClear();
      $this->DisplayFooter();
      $this->BaiduStatistic();
    }
    echo '</body>';
    echo '</html>';
  }

  /**
   * 显示网站LOGO
   */
  public function DisplayLogo(){
    global $base_url;
    $logo = '<div class="logo">'.l('<img src="'.$base_url.'/images/logo.png" alt="植物365" />', $base_url).'</div>';
    echo $logo;
  }

  /**
   * 显示页面标题
   */
  public function DisplayTitle(){
    echo '<title>'.$this->title.'</title>';
  }

  /**
   * 显示页面Meta数据
   */
  public function DisplayMeta(){
    $output = '<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />';
    if($this->meta_keywords){
      $output .= '<meta name="keywords" content="'.$this->meta_keywords.'">';
    }
    if($this->meta_description){
      $output .= '<meta name="description" content="'.$this->meta_description.'">';
    }
    echo $output;
  }

  /**
   * 加载CSS 样式 和 favicon.ico
   */
  public function DisplayStyles(){
    global $base_url;
    $output = '<link rel="shortcut icon" href="'.$base_url.'/images/favicon.ico" type="image/x-icon" />';
    $output .= '<link rel="stylesheet" href="'.$base_url.'/css/style.css" type="text/css" media="all">';
    $output .= '<link rel="stylesheet" href="'.$base_url.'/css/plant.css" type="text/css" media="all">';
    $output .= '<link rel="stylesheet" href="'.$base_url.'/css/gallery.css" type="text/css" media="all">';
    $output .= '<link rel="stylesheet" href="'.$base_url.'/css/article.css" type="text/css" media="all">';
    echo $output;
  }

  /**
   * 显示页面头部内容
   */
  public function DisplayHeader(){
    if(preg_match('/article[^list]/', $this->path, $match) && $this->pagenotfound === false) {
      $header_class = 'header';
    }elseif(preg_match('/plant\/([\s\S]*)/', $this->path, $match) && $this->pagenotfound === false){
      $header_class = 'header';
    }else {
      $header_class = 'front_header';
    }
    echo '<div class="'.$header_class.'">';
    $this->DisplayLogo();
    $this->DisplayMenu();
    echo '</div>';
    echo '<div class="clear"></div>';
  }

  /**
   * 显示菜单
   */
  public function DisplayMenu(){
    /* 全站菜单以及对应路径数组 */
//     $menus = site_menus();
    $taxonomys = taxonomy_vid_load(1);
    
    foreach($taxonomys as $key => $taxonomy){
        $menus[$key]['name']    = $taxonomy['name'];
        $menus[$key]['path']    = 'plant_category/'.$taxonomy['tid'];
        $menus[$key]['weight']  = $taxonomy['weight'];
    }

    $output = '<div class="menu">';
      $output .= '<ul>';
      foreach($menus AS $menu) {        
          $text = $menu['name'];
          $path = $menu['path'];
//           $weight = $menu['weight'];
          $menuOutputs[] = '<li>'.l(t($text), $path).'</li>';        
      }
      krsort($menuOutputs);
      $output .= implode('', $menuOutputs);

      $output .= '</ul>';
    $output .= '</div>';

    $output .= '<div class="submenu"></div>';

    echo $output;
  }

  /**
   * 显示导航条
   */
  public function DisplayBreadcrumb(){
    $output = '';
    $output .= '<div class="breadcrumb">';
    $output .= implode(' >> ', $this->breadcrumbs);
    $output .= '</div>';
    $output .= '<div class="dian"></div>';
    echo $output;
  }

  public function DisplayFrontContent(){
    global $base_url;

    $articles = article_pager_load();
    
    $pager = article_pager();
    $output = '<div class="frontpage_left_content">';
      $output .= '<ul>';
        if(is_array($articles) && count($articles)) {
          foreach($articles AS $article){
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
      if($pager) {
        $output .= $pager;
      }
      //首页百度广告
      $output .= '<br><br><div class="ad_front_bottom"><script type="text/javascript">var cpro_id = "u1587014";</script><script src="http://cpro.baidustatic.com/cpro/ui/c.js" type="text/javascript"></script></div>';
    $output .= '</div>';



    $output .= '<div class="frontpage_right_content">';
    $output .=  $this->GetRightBlock();
    $output .= '</div>';



    echo $output;
  }

  /**
   * 显示页面内容
   */
  public function DisplayContent(){
    $func = NULL;
    $content = false;
//    $content = call_user_func('page_404');

    /* 获取所有网站路径以及对应的回调函数 */
    $callbacks = path_items();

    foreach($callbacks AS $callback) {
      foreach($callback AS $path => $func){

        $path = str_replace('%', '[0-9]+', $path);
        $path = str_replace('/', '\/', $path);
        /* if == go to next cycle */

        if($path == $this->path || preg_match('/^'.$path.'$/', $this->path)){
          $content = call_user_func($func);
        }
      }
    }
    if(!$content){
      $content = call_user_func('page_not_found');
    }
    echo $content;
  }

  /**
   * 显示页脚内容
   */
  public function DisplayFooter(){
    $output = '<div class="footer">';
    $output .= '<br> &copy; 2012 www.zhiwu365.com 植物365 京ICP备09036132号-4';
    $output .= '<br><br> 信息来源于网络，服务于网民，旨在传播植物科普知识。网站中转载的资料及图片，其版权属原作者或页面内声明的版权人拥有。 站长邮箱: zhiwu365@163.com';
    $output .= '</div>';

    $output .= $this->friendlinks;
    echo $output;
  }

  /**
   * 清理页面浮动
   */
  public function DisplayPageClear(){
    $output = '<div class="clear"> </div>';
    echo $output;
  }

  public function DisplayPageNotFound(){
//    header('HTTP/1.1 404 Not Found');
//    header('status: 404 Not Found');

    echo '<script type="text/javascript">
    function isIFrameSelf(){try{if(window.top ==window){return false;}else{return true;}}catch(e){return true;}}
    function toHome(){ if(!isIFrameSelf()){ window.location.href="http://www.zhiwu365.com";}}
    window.setTimeout("toHome()",5000);</script>';

    echo '<div class="header">';
    $this->DisplayLogo();
    echo '<div class="submenu"></div>';
    echo '</div>';
    echo '<div class="clear"></div>';
    echo '<div class="main"><br><h3>页面没有找到 5秒钟之后将会带您进入首页!</h3></div>';
  }

  /**
   * 获取右侧显示内容
   */
  public function GetRightBlock(){
    global $base_url;

    $gallerys = gallery_load();
    krsort($gallerys);
   
    $output = '';
    $output .= '<ul>';
    $i = 0;
    foreach($gallerys AS $gallery){
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
    return $output;
  }

  /**
   * 加载百度统计
   */
  public function BaiduStatistic(){
    $output = '<div class="tongji">';
    $output .= '<script type="text/javascript">
    var _bdhmProtocol = (("https:" == document.location.protocol) ? " https://" : " http://");
    document.write(unescape("%3Cscript src=\'" + _bdhmProtocol + "hm.baidu.com/h.js%3Fd425079352a087acf726a6d3a609ca25\' type=\'text/javascript\'%3E%3C/script%3E"));
    </script>
    ';
    $output .= '</div>';
    echo $output;
  }
}

/**
 * 显示首页内容;
 */
function page_display_frontpage(){
  global $site_name, $meta_keywords, $meta_description;

  $friendlinks = array(
    'http://www.freeskyf.net'   => t('自由聆听网'),
    'http://www.tczihua.com'    => t('天朝字画网'),
    'http://www.dingmx.com'     => t('鼎铭轩'),
    'http://www.36yg.com'       => t('一元云购'),
    'http://www.qiwen360.com'   => t('奇闻啦'),
    'http://www.518duoke.com'   => t('多客桥'),
    'http://www.tclvhua.com/'   => t('美国红枫树'),
    'http://www.188miaomu.com/' => t('绿化苗木'),
//     'http://www.fatong0312.com/'=> t('法桐'),
    'http://www.jsyxjg.com/'    => t('银杏树价格'),
    'http://www.pcdgh.com/'     => t('浦城丹桂'),
    'http://www.bjviu.com/'     => t('核桃苗批发'),
    'http://www.rsdongzao.com/'     => t('沾化冬枣'),
//     'http://www.xdnyzz.com/' => t('现代农业科技'),
  );
  $page = new Page();
  $page->SetTitle($site_name);
  $page->SetMetaKeywords($meta_keywords);
  $page->SetMetaDescription($meta_description);
  $page->SetFriendlinks($friendlinks);
  $page->DisplayPage();
}

/**
 * 显示页面内容;
 */
function page_display_content($arg){
  global $site_name, $meta_keywords, $meta_description;

  $page = new Page();
  $page->SetTitle($site_name);
  $page->SetMetaKeywords($meta_keywords);
  $page->SetMetaDescription($meta_description);

  $page->DisplayPage();
}

/**
 * 显示未知页面 404报错
 */
function page_not_found(){
    $data['menus'] = page_get_menu();
    $data['title'] = '页面没有找到';
    $output = theme('page_not_found', $data);
    echo $output;
    die();
}

?>