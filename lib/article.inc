<?php

/* 文章路径 */
define('ARTICLE_DATA_PATH', DOCUMENT_ROOT.OS_SLASH.'articledata'.OS_SLASH);
define('ARTICLE_CATEGORY_INDEX', DOCUMENT_ROOT.OS_SLASH.'articledata'.OS_SLASH.'category.index');
define('ARTICLE_INDEX', DOCUMENT_ROOT.OS_SLASH.'articledata'.OS_SLASH.'article.index');

define('ARTICLE_PHP_FILE', 'article_new.php');
define('ARTICLE_PHP_SUBMIT_FILE', 'article_new_submit.php');
define('ARTICLE_UPLOAD_PATH', UPLOAD_PATH.OS_SLASH.'article'.OS_SLASH);

$page_clear = page_clear();

/**
 * 植物页面显示类
 */
class PageArticle extends Page{

  /**
   * 显示类型
   */
  public $article_displaytype = 'detail';

  /**
   * 文章信息
   */
  public $article;

  /**
   * 设置文章信息
   */
  public function SetArticle($value){
    $this->article = $value;
  }

  /**
   * 设置文章显示类型
   */
  public function SetArticleDisplayType($value){
    $this->article_displaytype = $value;
  }

  /**
   * 显示页面内容
   */
  public function DisplayContent(){
    $displayType = $this->article_displaytype;
    switch($displayType){
      case 'list':
        echo '<div class="article_overview_wrapper">';
        $this->DisplayBreadcrumb();
        $this->DisplayOverview();
        echo '</div>';
        break;
      case 'detail':
        echo '<div class="article_detail_wrapper">';
        $this->DisplayBreadcrumb();
        $this->DisplayDetail();
        echo '</div>';
    }
  }

  /**
   * 显示总览页面
   */
  public function DisplayOverview(){
    echo 'overview';
  }

  /**
   * 显示详细页面
   */
  public function DisplayDetail(){
    global $clear;

    $article = $this->article;

    if($this->pagenotfound === true){
      echo call_user_func('page_not_found');
      return false;
    }
    if(is_array($article) && count($article)){
      $title = $article[0]['title'];

      /* 处理页面输出 */
      $content = article_filter_output($article[0]['id'], $article[0]['content']);

    }else {
      $output = '<div class="content">Content not found</div>';
      echo $output;
    }


    /* content */
    $output ='<div class="content">';
      $output .='<div class="content_wrapper">';
        $output .='<div class="title"><h1>'.$title.'</h1></div>';
        $output .='<div class="text">';
        $output .= $content;
        $output .= '</div>';

        $output .= '<div class="article_info">';
          $output .= '<ul>';
          $output .= '<li>发布日期<b>:</b> '.date('Y-m-d', trim($article[0]['created'])).'<li>';
          $output .= '<li>来源<b>:</b> '.$article[0]['source'].'<li>';
          $output .= '<li>作者<b>:</b> '.$article[0]['author'].'<li>';
          $output .= '<li>欢迎投稿<b>:</b> zhiwu365@163.com <li>';
          $output .= '</ul>';
        $output .= '</div>';

      $output .= '</div>';
    $output .= '</div>';

    $output .= '<div class="clear"></div>';
    //百度文章页广告
    $output .= '<div class="ad_article_bottom"><script type="text/javascript">var cpro_id = "u1587208";</script><script src="http://cpro.baidustatic.com/cpro/ui/c.js" type="text/javascript"></script></div>';

    echo $output;
  }
}

function article_display_content($arg=NULL){
    global $page_title;
    $pagenotfound = false;
    
    switch($arg[0]){
    case 'article':
      //检查文章ID
      $id = $arg[1];
      if(!empty($id) && article_check_id($id) && $article = article_load($id)){
        $title                  = $article[0]['title'];
        $article_displaytype    = 'detail';
        $meta_keywords          = $article[0]['meta_keywords'];
        $meta_description       = $article[0]['meta_description'];
        $breadcrumbs[]['title'] = $title;
      }else{
        $pagenotfound = true;
      }
    break;
    
    case 'article_category':
      //暂时没有.
    break;
    }
    
    $page = new PageArticle();
    
    if($pagenotfound){
        $page->SetPagenotfound($pagenotfound);
        $page->SetTitle('页面没有找到');
    }else{
        $page->SetArticleDisplayType($article_displaytype);
        $page->SetTitle($title.'_'.$page_title);
        $page->SetMetaKeywords($meta_keywords);
        $page->SetMetaDescription($meta_description);
        $page->SetArticle($article);
        $page->SetBreadcrumb($breadcrumbs);
    }
    
    $page->DisplayPage();
}


/**
 * 读取所有文章
 */
function article_load($id=NULL){
    $db = new database;
    
    $articles = false;

    //表路径
    $table = DB_PATH.TABLE_ARTICLE;
    
    if($id){
        $where = array('id'=>$id);
        $articles = $db->db_select($table, $where);
    }else{
        $xml  = simplexml_load_file($table);
        $articles = $xml->xpath("article");        
    }
    
    if(is_array($articles) && count($articles)){
        foreach($articles as $article){
            $new_article = (array)$article;
            
            //添加图片信息
            $article_image_path = UPLOAD_PATH.OS_SLASH.'article'.OS_SLASH.$new_article['id'];
            
            $images_temp = file_get_folder_names($article_image_path);
            
            $images = array();
            if(is_array($images_temp) && count($images_temp)){
                $new_article['image_yes'] = true;
                foreach($images_temp AS $image) {
                    $images[] = $image;
                }
                $new_article['images'] = $images;
            }else{
                $new_article['image_yes'] = false;
            }
            
            $new_articles[] = $new_article;
        }
        
        $articles = $new_articles;
        
    }
    
    return  $articles;
}

/**
 * 分页读取文章
 * @param string $tid
 * @return $article_pagers
 */
function article_pager_load($tid=NULL){
    $pager_id = 1;
    if(@$_REQUEST['pager']){
        $pager_id = $_REQUEST['pager'];
    }

    $article_pagers = false;
    $pager_limit = PAGER_LIMIT;

    if($tid){
        $articles = article_load(array('tid'=>$tid));
    }else{
        $articles = article_load();
        
    }
    krsort($articles);
    
    /* 计算起始位置 */
    if($pager_id == 1){
        $start = 0;
        $end = $pager_limit - 1;
    }elseif($pager_id == 2) {
        $start = $pager_limit;
        $end = $start+$pager_limit-1;
    }else{
        $start = $pager_limit*($pager_id-1);
        $end = $start+$pager_limit-1;
    }

    
    $i = 0;
    foreach($articles AS $article) {
        if($i >= $start && $i <=$end){
            $article_pagers[] = $article;
        }
        $i++;
    }

    return $article_pagers;
}

/**
 * 文章分页显示
 */
function article_pager($tid=NULL){
  $pager_id = 1;
  if(@$_REQUEST['pager']){
    $pager_id = $_REQUEST['pager'];
  }

  $pager_html = false;
  $pager_limit = PAGER_LIMIT;

  $articles = article_load();
  $count=count($articles);

  if($count) {
    /* How many pages */
    $pages = ceil($count / $pager_limit);
    if($pages > 1) {
      $pages = $pages + 1;
      /* Generate HTML pager */
      $pager_html = '<div class="pager">';
      $pager_html .= '<ul>';

      for($i=1; $i < $pages; $i++){

        if($i != $pager_id){

          if($i == 1){
            $pager_html .= '<li >'.l($i, '&pager='.$i).'</li>';
          }else {
            if($tid){
              $pager_html .= '<li>'.l($i, 'article_category/'.$tid.'?pager='.$i).'</li>';
            }else{
              $pager_html .= '<li>'.l($i, '&pager='.$i).'</li>';
            }
          }
        }else {
          $pager_html .= '<li class="page_current">'.$i.'</li>';
        }
      }
      $pager_html .= '</ul>';
      $pager_html .= '</div>';
    }else {
      return false;
    }
  }
  return $pager_html;
}

/**
 * 检查文章是否存在.
 */
function article_check_id($id){
  if(!is_numeric($id)) {
    return false;
  }

  if($id <= 0){
    return false;
  }

  return true;
}

/**
 *
 */
function article_filter_output($aid, $content){
  global $base_url;

  //替换制表符
  $content = preg_replace('/\t/', '&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;',$content);

  //替换' '
  $content = html_blankspace_replace($content);

  //替换换行符
  $content = nl2br($content);

  //替换文章图片路径 (__ARTICLE_IMAGE_PATH__)
  $path = $base_url.'/uploads/article/'.$aid;
  $content = preg_replace('/__AIP__/', $path, $content);

  return $content;
}

function article_transfer_load(){
	$articles = article_load_old();

	return $articles;
}

/**
 * 迁移内容数据
 */
function article_transfer_content($articles){
    global $base_url;
    
    $db = new database;
    
    //表路径
    $table_article = DB_PATH.TABLE_ARTICLE;
    
    //翻转数组
    krsort($articles);
    
    foreach($articles as $article){
    
        //获取数据
        $v = $db->db_select($table_article);
    
        //计算起始ID
        $attributes = (array)$v->attributes();
        if(is_array($attributes) && count($attributes)){
            foreach($attributes as $key => $value){
                $start_id = $value['start_id']+ 1;
            }
        }else{
            $start_id = 1;
        }
    
        $attributes = array('start_id'=>$start_id);
        
        $tid                = article_transfer_content_get_new_tid($article->tid);
        $title              = (array)$article->title;
        $title              = $title[0];
        $meta_keywords      = (array)$article->meta_keywords;
        $meta_keywords      = $meta_keywords[0];
        $meta_description   = (array)$article->meta_description;
        $meta_description   = $meta_description[0];
        $source             = (array)$article->source;
        $source             = $source[0];
        $author             = (array)$article->author;
        $author             = $author[0];
        $created            = (array)$article->created;
        $created            = $created[0];
        $updated            = (array)$article->updated;
        $updated            = $updated[0];
        $teaser             = (array)$article->teaser;
        $teaser             = $teaser[0];
        $content            = (array)$article->content;
        $content            = $content[0];

        
        //生成数据
        $data['article'] = array(
            'id'                    => $start_id,
            'tid' 		            => $tid,
            'status' 		        => 1,
            'title' 	            => $title,
            'meta_keywords' 	    => $meta_keywords,
            'meta_description' 	    => $meta_description,
            'source'		        => $source,
            'author' 		        => $author,
            'created'	            => $created,
            'updated'               => $updated,
            'teaser'                => $teaser,
            'content'               => $content,
        );
    
        //写入article.xml
        $db->db_insert($table_article, $data, $attributes);
    
    }    
}

/**
 * 迁移内容数据
 */
function article_transfer_content_get_new_tid($tid){
    switch($tid){
        case 1:
            $old_name = '趣味植物';
            break;
        case 2:
            $old_name = '植物新闻';
            break;
        case 3:
            $old_name = '植物科学';
            break;
        case 4:
            $old_name = '植物之最';
            break;
        case 5:
            $old_name = '植物知识';
            break;
        case 6:
            $old_name = '植物历史';
            break;
        case 7:
            $old_name = '植物故事';
            break;
        case 8:
            $old_name = '植物保护';
            break;
        case 9:
            $old_name = '植物学家';
            break;
        case 10:
            $old_name = '植物名词';
            break;
        case 11:
            $old_name = '每日养眼';
            break;
    }
    
    $db = new database;
    //表路径
    $table = DB_PATH.TABLE_TAXONOMY_TERM_DATA;
    
    //获取数据
    $where = array('name'=>$old_name);
    $t = $db->db_select($table, $where);
    
    $new_tid = $t[0]['tid'];

    
    return $new_tid;
}

/**
 * 读取文章。读取方法
 * 1. 读取category.index文件，获取信息.
 * 2. 读取article.index文件, 获取文件夹名字, 以及ID号
 * 3. 组合路径, 遍历所有文件夹获取内容，以及图片地址.
 * @retrun array()
 */
function article_load_old($aid = NULL){
    $articles = false;

    // 判断读取篇文章，或者读取所有文章.
    if(!empty($aid)) {
        /* 1. 读取article.index */
        $articleIndexes = file_handle_UFT8(file(ARTICLE_INDEX));

        /* 2. 循环遍历 生成数组 $nodes_temp */
        foreach($articleIndexes AS $articleIndex) {
            $articleIndex = explode('|', $articleIndex);
            $articleid = trim($articleIndex[0]);
            $tid = trim($articleIndex[1]);
            $is_frontpage = trim($articleIndex[2]);

            if($articleid == $aid){
                $node = new stdClass();
                $node->nid = $articleid;
                $node->tid = $tid;
                $node->is_frontpage = $is_frontpage;
                $nodes_temp[] = $node;

                /* 3. 获取内容 和 图片*/
                if(is_array($nodes_temp) && count($nodes_temp)){
                    foreach($nodes_temp AS $node) {
                        $ariticle_path = ARTICLE_DATA_PATH.'contents'.OS_SLASH.'article_'.$articleid.'.xml';
                        $xml=simplexml_load_file($ariticle_path);
                        $node->title = $xml->title;
                        $node->meta_keywords = $xml->meta_keywords;
                        $node->meta_description = $xml->meta_description;
                        $node->source = $xml->source;
                        $node->author = $xml->author;
                        $node->created = $xml->created;
                        $node->updated = $xml->updated;
                        $node->teaser = $xml->teaser;
                        $node->content = $xml->content;
                        //            $node->path = $category[4].'/'.$articleid;

                        // 获取文章 图片路径
                        $article_image_path = ARTICLE_DATA_PATH.'images'.OS_SLASH.$node->nid;

                        $images_temp = file_get_folder_names($article_image_path);

                        if(is_array($images_temp) && count($images_temp)){
                            $node->image_yes = true;
                            foreach($images_temp AS $image) {
                                $images[] = $image;
                            }
                            $node->images = $images;
                        }else{
                            $node->image_yes = false;
                        }

                        $articles[] = $node;
                    }
                }
            }
        }
    }else {

        /* 1. 读取article.index */
        $articleIndexes = file_handle_UFT8(file(ARTICLE_INDEX));

        /* 2. 循环遍历 生成数组 $nodes_temp */
        foreach($articleIndexes AS $articleIndex) {
            $articleIndex = explode('|', $articleIndex);

            $articleid = trim($articleIndex[0]);
            $tid = trim($articleIndex[1]);
            $is_frontpage = trim($articleIndex[2]);
            $ariticle_path = ARTICLE_DATA_PATH.'contents'.OS_SLASH.'article_'.$articleid.'.xml';

            $node = new stdClass();
            $node->nid = $articleid;
            $node->tid = $tid;
            $node->status = $is_frontpage;

            $xml=simplexml_load_file($ariticle_path);
            $node->title = $xml->title;
            $node->meta_keywords = $xml->meta_keywords;
            $node->meta_description = $xml->meta_description;
            $node->source = $xml->source;
            $node->author = $xml->author;
            $node->created = $xml->created;
            $node->updated = $xml->updated;
            $node->teaser = $xml->teaser;
            $node->content = $xml->content;
            //      $node->path = $category[4].'/'.$articleid;

            $nodes_temp[] = $node;
        }

        /* 倒叙配列 最新发布的文章显示在最上面 */
        $nodes_temp = array_reverse($nodes_temp);

        /* 3. 获取内容 和 图片*/
        if(is_array($nodes_temp) && count($nodes_temp)){
            foreach($nodes_temp AS $node) {
                // 获取文章 - 图片路径
                $article_image_path = ARTICLE_DATA_PATH.OS_SLASH.'images'.OS_SLASH.$node->nid;

                $images_temp = file_get_folder_names($article_image_path);

                $images = array();
                if(is_array($images_temp) && count($images_temp)){
                    $node->image_yes = true;
                    foreach($images_temp AS $image) {
                        $images[] = $image;
                    }
                    $node->images = $images;
                }else{
                    $node->image_yes = false;
                }

                $articles[] = $node;
            }
        }
    }

    return $articles;
}
?>
