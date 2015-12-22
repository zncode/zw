<?php

/**
 * 后台HTML页面
 */
function theme_admin_html_output($title, $menus=array(), $content='', $css, $js){
	global $base_url;
	@$message = $_REQUEST['message'];

	$output = '';
	$output .= '<!DOCTYPE html><html lang="zh">';
	$output .= '<head>';
	$output .= '<title>'.$title.'</title>';
	$output .= $css;
	$output .= $js;
	$output .= '<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />';
	$output .= '</head>';
	$output .= '<body>';
	$output .= '<div class="menu">';
	$output .= '<ul>';
	foreach($menus AS $key => $value){
		$output .= '<li><a href="'.$key.'">'.$value.'</a></li>';
	}
	$output .= '</ul>';
	$output .= '</div>';

	if($message){
		$output .= '<div class="message">';
		$output .= $message;
		$output .= '</div>';
	}

	$output .= '<div class="main">'.$content.'</div>';

	$output .= '</body>';
	$output .= '</html>';

	return $output;
}

function theme_table($id, $headers, $rows=array()){
	$output = '<table id="'.$id.'">';

	$output .= '<tr>';
	foreach($headers as $value){
		$output .= '<th width="'.$value['width'].'" align="'.$value['align'].'">'.$value['title'].'</th>';
	}
	$output .= '</tr>';

	if(count($rows)){
		foreach($rows AS $value){
			$output .= '<tr>';
				foreach($value as $value1){
					$output .= '<td>'.$value1.'</td>';
				}
			$output .= '</tr>';
		}
	}else{
		$output .= '<tr><td>无数据</td></tr>';
	}
	$output .= '</table>';

	return $output;
}

/**
 * 调用模板
 * @param string $template_file
 * @param array $data
 */
function theme($template_file, $data=array()){
    global $base_url, $site;
    $output = '';
    if($template_file =='page_not_found'){
        require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. 'web' .DIRECTORY_SEPARATOR.'theme' .DIRECTORY_SEPARATOR. $template_file.'.tpl.php';
    }else{
        require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. $site.DIRECTORY_SEPARATOR.'theme' .DIRECTORY_SEPARATOR.'header.tpl.php';
        require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. $site.DIRECTORY_SEPARATOR.'theme' .DIRECTORY_SEPARATOR. $template_file.'.tpl.php';
        if($template_file !='index'){
            require_once DOCUMENT_ROOT. DIRECTORY_SEPARATOR. $site.DIRECTORY_SEPARATOR.'theme' .DIRECTORY_SEPARATOR.'footer.tpl.php';
        }        
    }

    return $output;
}
?>