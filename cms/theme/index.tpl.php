<?php 
$i= 1;
foreach($data['menus'] AS $menu){
    $output .= $i.' > '.$menu.'<br><br>';
    $i++;
}
$output .= '</body>';
$output .= '</html>';
?>