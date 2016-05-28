<?php
/**
 * @file
 */

/**
 * class
  $FetchAction = new FetchAction();
  $FetchAction->fetchAllChannel();
 */
class FetchAction {
  /** - - - - - - action - - - - - - - - - - - - - - - - - - - - - - - - - -  */
  /**
   * @param, Channel Status is Enable or Disable
   * @return, tids array
   */
  public function allChannelTids($enable = TRUE) {
    $channel_tids = array();

    $terms = taxonomy_get_tree(2);
    if (is_array($terms)) {
      foreach ($terms as $term) {
        $TermChannelInfo = new TermChannelInfo($term->tid);
        if ($enable) {
          if ($TermChannelInfo->fieldValue('field_channel_status') == 1) {
            $channel_tids[] = $term->tid;
          }
        }
        else {
          $channel_tids[] = $term->tid;
        }
      }
    }

    return $channel_tids;
  }

  /**
   * @param, Channel Status is Enable or Disable
   * @return, tids array
   */
  public function checkEpgNid($channel_tid = NULL, $channel_program_date = NULL) {
    $NodeEpgQuery = new NodeEpgQuery();
    $nids = $NodeEpgQuery->nodesByBundle(array('epg'));
    $nids = $NodeEpgQuery->nodesByChannelTids(array($channel_tid), $nids);
    $nids = $NodeEpgQuery->nodesByDate($channel_program_date, $nids);

    $output = NULL;
    if (is_array($nids)) {
      $output = current($nids);
    }
    else {
      $NodeAction = new NodeAction('epg');
      $output = $NodeAction->insertNodeByDateField($channel_program_date);
    }

    return $output;
  }

  /**
   * @param, batch to call
   * @return,
   */
  public function fetchAllChannel($enable = TRUE) {
    $channel_tids = $this->allChannelTids($enable);

    if (is_array($channel_tids)) {
      foreach ($channel_tids as $channel_tid) {
        $channel_raw_content = $this->getChannelRawContent($channel_tid);
        $channel_program     = $this->getChannelProgram($channel_tid, $channel_raw_content);
        if ($channel_program) {
          $node_nid = checkEpgNid($channel_tid, $channel_program['program_date']);

          $NodeAction = new NodeAction('epg');
          $NodeAction->insertNodeFields($channel_program);
          $NodeAction->updateFields($channel_program);
        }
      }
    }
  }

  /**
   * @param, Channel Rule
   * @return
   */
  public function filterContent($channel_rule = NULL, $channel_raw_content = NULL) {
    $output = NULL;

    if ($channel_rule) {
      preg_match_all($channel_rule, $channel_raw_content, $matches);
      $output = $matches;
    }

    return $output;
  }

  /**
   * use rule to get program date and content
   * @param, Channel Tid
   * @return,
     array(
       'program_date' => 2016-05-24
       'program_content' => array(),
     );
   */
  public function getChannelProgram($channel_tid = NULL, $channel_raw_content = NULL) {
    $output = NULL;

    if ($channel_tid) {
      $TermChannelInfo  = new TermChannelInfo($channel_tid);
      $channel_url      = $TermChannelInfo->fieldValue('field_channel_url');
      $channel_rule     = $this->guangXiRule();

      if ($channel_url && $channel_rule) {
        $output['program_date']    = format_date(time(), 'custom', 'Y-m-d', 'Hongkong');
        $output['program_content'] = filterContent($channel_rule, $channel_raw_content);
      }
    }

    return $output;
  }

  /**
   * @param, Channel Tid
   * @return
   */
  public function getChannelRawContent($channel_tid = NULL) {
    $output = NULL;

    if ($channel_tid) {
      $TermChannelInfo = new TermChannelInfo($channel_tid);
      $channel_url     = $TermChannelInfo->fieldValue('field_channel_url');
      if ($channel_url) {
        $output = $this->getContentByCurl($channel_url);
        dpm($output);
      }
    }

    return $output;
  }

  /**
   * instead of using file_get_contents($channel_url);
   */
  function getContentByCurl($Url = NULL) {
    if (!function_exists('curl_init')){
      die('CURL is not installed!');
    }

    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, $Url);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);

    $result = curl_exec($ch);
    if ($result === false) {
      throw new Exception('Can not download URL');
    }
    else {
      $output = $result;
    }

    curl_close($ch);

    return $output;
  }

  /**
   * @param, Channel Tid
   * @return
   */
  public function guangXiRule() {
    $output = NULL;

    return $output;
  }

  /**
   * @param, Channel Tid
   * @return
   */
  public function guangXiContent() {
    $output = addslashes('<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<meta name="robots" content="index,follow" />
<meta name="keywords" content="广西电视台 节目单" />
<meta name="description" content="节目单" />
<meta name="copyright" content="广西网络广播电视台" />
<meta name="owner" content="广西网络广播电视台" />
<meta name="contact" content="0771-2196602 0771-2196604" />
<meta name="email" content="gxtvc217@163.com" />
<meta name="Author" content="广西网络广播电视台" />
<title>节目单--广西网络广播电视台</title>
    <link href="css/default_style.css" rel="stylesheet" type="text/css" />
    <link href="css/style.css" rel="stylesheet" type="text/css" />
    <link href="http://www.gxtv.cn/css/ads.css" rel="stylesheet" type="text/css" />
    <script type="text/javascript" src="/js/jquery-1.8.2.min.js"></script>
    <script type="text/javascript" src="js/default.js"></script>
    <script type="text/javascript" src="js/Calendar.js"></script>
    <script type="text/javascript" src="http://www.gxtv.cn/js/user_login.js"></script>
<script type="text/javascript" src="http://www.gxtv.cn/js/ads.js"></script>
</head>
<body>

<!--通行证 -->
<div class="Top">
<div class="login">
    <div class="Member" id="UserLogin"></div>
    <div id="globalSearch">
        <script type="text/javascript" src="http://www.gxtv.cn/js/searchform.js"></script>
    </div>
</div>
</div>

<!--G_Menu全局导航 -->
<div class="G_Menu">
<div class="Cont">
<div class="logo"><a href="http://www.gxtv.cn"><img src="http://www.gxtv.cn/images/gxtv_logo.gif"  alt="广西网络广播电视台首页"/></a></div>
<div class="live"></div>
<div class="menu">
<div class="nav">
<a class="home" href="http://www.gxtv.cn/">首页</a>|
<a href="http://news.gxtv.cn/">新闻</a>|
<a href="http://ent.gxtv.cn/">娱乐</a>|
<a href="http://fashion.gxtv.cn/">时尚</a>|
<a href="http://art.gxtv.cn/">丹青</a>|
<a href="http://book.gxtv.cn/">阅读</a>|
<a href="http://asean.gxtv.cn/">东盟</a>|
<a href="http://shop.mltx.cn/">电商</a>|
<a href="http://www.mltx.cn/"><font color="#ff0000">美丽天下</font></a>|
<a href="http://child.gxtv.cn/">青少</a>|
<a href="http://dv.mltx.cn/">原创</a>|
<a href="http://sports.gxtv.cn/">体育</a>|
<a href="http://ly.gxtv.cn/">旅游</a>|
<a href="http://house.gxtv.cn/">房产</a>|
<a href="http://happyhour.gxtv.cn/">夜文化</a></div>
<div class="subnav">
<a class="home" href="http://vod.gxtv.cn/WeiShi.html">广西卫视</a>
<a href="http://vod.gxtv.cn/ZongYi.html">综艺频道</a>
<a href="http://vod.gxtv.cn/DuShi.html">都市频道</a>
<a href="http://vod.gxtv.cn/ZiXun.html">新闻频道</a>
<a href="http://vod.gxtv.cn/YingShi.html">影视频道</a>
<a href="http://vod.gxtv.cn/GongGong.html">公共频道</a>
<!--<a href="http://tv.gxtv.cn/tv-7.html">国际频道</a>-->
<a href="http://tv.gxtv.cn/tv-8.html">乐思购频道</a>
<a href="http://vod.gxtv.cn/JiaoTong.html">睛彩广西交通</a>
<a href="http://program.gxtv.cn/">节目表</a>
</div>
</div>
</div>
</div>
<!--G_Menu end -->
    <!--banner -->
    <div class="AD" id="181"></div>
    <!--频道列表-->
    <div class="TV_tab">
        <ul>
            <li class="on"><a href="#">广西卫视</a></li>
            <li><a href="#">综艺频道</a></li>
            <li><a href="#">都市频道</a></li>
            <li><a href="#">新闻频道</a></li>
            <li><a href="#">影视频道</a></li>
            <li><a href="#">公共频道</a></li>
            <li><a href="#">国际频道</a></li>
            <li><a href="#">乐思购</a></li>
        </ul>
    </div>
    <!--星期列表-->
    <div class="week_tab">
        <ul>
            <li><a href="#">
                <h3>
                    星期一</h3>
                <p>
                    2012-02-06</p>
            </a></li>
            <li><a href="#">
                <h3>
                    星期二</h3>
                <p>
                    2012-02-07</p>
            </a></li>
            <li><a href="#">
                <h3>
                    星期三</h3>
                <p>
                    2012-02-08</p>
            </a></li>
            <li><a href="#">
                <h3>
                    星期四</h3>
                <p>
                    2012-02-09</p>
            </a></li>
            <li><a href="#">
                <h3>
                    星期五</h3>
                <p>
                    2012-02-10</p>
            </a></li>
            <li><a href="#">
                <h3>
                    星期六</h3>
                <p>
                    2012-02-11</p>
            </a></li>
            <li><a href="#">
                <h3>
                    星期天</h3>
                <p>
                    2012-02-12</p>
            </a></li>
        </ul>
    </div>
    <div class="grA">
        <div class="grA_L">
            <!--日期表-->
            <div class="Date">
                <table border="0" cellpadding="0" cellspacing="2" class="Calendar" id="caltable">
                    <thead>
                        <tr align="center" valign="middle">
                            <td colspan="7" class="Title">
                                <a href="javaScript:subMonth();" title="上一月" class="DayButton">&#9668;</a>
                                <input name="year" id="year" type="text" size="4" maxlength="4" onkeydown="javascript:if(event.keyCode==13){setDate();} "
                                    onkeyup="this.value=this.value.replace(/[^0-9]/g,'')" onpaste="this.value=this.value.replace(/[^0-9]/g,'')" />
                                年
                                <input name="month" id="month" type="text" size="1" maxlength="2" onkeydown="javascript:if(event.keyCode==13){setDate();} "
                                    onkeyup="this.value=this.value.replace(/[^0-9]/g,'')" onpaste="this.value=this.value.replace(/[^0-9]/g,'')" />
                                月 <a href="JavaScript:addMonth();" title="下一月" class="DayButton">&#9658;</a>
                            </td>
                        </tr>
                        <tr align="center" valign="middle">
                            <script language="JavaScript">
                                document.write("<TD class=DaySunTitle id=diary >" + days[0] + "</TD>");
                                for (var intLoop = 1; intLoop < days.length - 1; intLoop++)
                                    document.write("<TD class=DayTitle id=diary>" + days[intLoop] + "</TD>");
                                document.write("<TD class=DaySatTitle id=diary>" + days[intLoop] + "</TD>");
                            </script>
                        </tr>
                    </thead>
                    <tbody border="1" cellspacing="0" cellpadding="0" id="calendar" align="CENTER" onclick="getDiary()">
                        <script language="JavaScript">
                            for (var intWeeks = 0; intWeeks < 6; intWeeks++) {
                                document.write("<TR style='cursor:hand'>");
                                for (var intDays = 0; intDays < days.length; intDays++) document.write("<TD class=CalendarTD onMouseover='buttonOver();' onMouseOut='buttonOut();'></TD>");
                                document.write("</TR>");
                            }
                        </script>
                    </tbody>
                </table>
                <script language="JavaScript">
                    Calendar();
                </script>
                <input type="hidden" id="hd_select_date" name="hd_select_date" />
            </div>
            <!--节目搜索-->
            <div class="Program_search">
                <h2 class="Program_search_T">
                </h2>
                <div class="Cont">
                    <ul>
                        <form action="#">
                        <li>
                            <input type="text" name="search_content" id="search_content" value="" /></li>
                        <li><span class="n1">
                            <select name='ChannelID' id="ChannelID">
                                <option value=''>所属频道</option>
                                <option value='广西卫视'>广西卫视</option>
                                <option value='综艺频道'>综艺频道</option>
                                <option value='都市频道'>都市频道</option>
                                <option value='新闻频道'>新闻频道</option>
                                <option value='影视频道'>影视频道</option>
                                <option value='公共频道'>公共频道</option>
                                <option value='乐思购'>乐思购</option>
                                <option value='国际频道'>国际频道</option>
                            </select></span> <span class="n2">
                                <input class="sel" id="search_button" name="search_button" style="cursor: pointer;"
                                    type="button" value="" />
                            </span></li>
                        </form>
                    </ul>
                </div>
            </div>
            <!--本台节目-->
            <div class="My_Program">
                <h2 class="My_Program_T">
                    <span class="capmore"><a href="http://vod.gxtv.cn/" target="_blank">更多>></a></span></h2>
                <div class="Cont">

                <div class="Cimglist">
                        <a href="http://vod.gxtv.cn/VodView-246-0.html" target="_blank"><img src="http://upfile.gxtv.cn/vod/201605111727198946.jpg" /></a>
                        <p>寻找太阳</p>
                </div>

                <div class="Cimglist">
                        <a href="http://vod.gxtv.cn/VodView-245-0.html" target="_blank"><img src="http://upfile.gxtv.cn/vod/201605111328418008.jpg" /></a>
                        <p>大战人熊婆</p>
                </div>

                <div class="Cimglist">
                        <a href="http://vod.gxtv.cn/VodView-244-0.html" target="_blank"><img src="http://upfile.gxtv.cn/vod/201605101413436290.jpg" /></a>
                        <p>灯花儿</p>
                </div>

                <div class="Cimglist">
                        <a href="http://vod.gxtv.cn/VodView-243-0.html" target="_blank"><img src="http://upfile.gxtv.cn/vod/201605061738431133.jpg" /></a>
                        <p>达稼与达伦</p>
                </div>

                <div class="Cimglist">
                        <a href="http://vod.gxtv.cn/VodView-242-0.html" target="_blank"><img src="http://upfile.gxtv.cn/vod/201604211607105508.jpg" /></a>
                        <p>心声力量</p>
                </div>

                <div class="Cimglist">
                        <a href="http://vod.gxtv.cn/VodView-241-0.html" target="_blank"><img src="http://upfile.gxtv.cn/vod/201604211555295821.jpg" /></a>
                        <p>艾问顶级投资人创客法则</p>
                </div>

                <div class="Cimglist">
                        <a href="http://vod.gxtv.cn/VodView-233-0.html" target="_blank"><img src="http://upfile.gxtv.cn/vod/201602151149311218.jpg" /></a>
                        <p>2016广西少儿舞蹈电视精品节目展</p>
                </div>

                <div class="Cimglist">
                        <a href="http://vod.gxtv.cn/VodView-232-0.html" target="_blank"><img src="http://upfile.gxtv.cn/vod/201602051805592476.jpg" /></a>
                        <p>少数民族民间故事动画系列片</p>
                </div>

                </div>
            </div>
        </div>
        <div class="grA_R">
            <!--节目时间表-->
            <div class="Program_guide">
                <h2 class="Program_guide_T">
                    <span class="capname"></span><span class="capmore"></span>
                </h2>
                <div class="Cont">
                    <div class="Clist1">
                        <ul>

                                 <li><span>00:08</span>财富最前线 12'</li>

                                 <li><span>00:21</span>重播:观复嘟嘟(两期) 60'</li>

                                 <li><span>01:41</span>重播:第一书记 60'</li>

                                 <li><span>03:00</span>重播:时尚中国</li>

                                 <li><span>03:20</span>纪录片:大抗战</li>

                                 <li><span>04:10</span>黎明剧场:30集:我是传奇(24)</li>

                                 <li><span>05:10</span>黎明剧场:30集:我是传奇(25)</li>

                                 <li><span>06:00</span>纪录 25'</li>

                                 <li><span>06:35</span>广西旅游天气预报</li>

                                 <li><span>06:36</span>广西海洋天气预报</li>

                                 <li><span>06:40</span>重播:新闻大通道</li>

                                 <li><span>07:06</span>重播:广西新闻前 1'</li>

                                 <li><span>07:15</span>重播:广西新闻</li>

                                 <li><span>07:49</span>收视预告(1)</li>

                                 <li><span>07:51</span>周末早栏目重播前 1'</li>

                                 <li><span>08:00</span>重播:第一书记 60'</li>

                                 <li><span>09:22</span> </li>

                                 <li><span>09:22</span> </li>

                                 <li><span>09:23</span>收视预告(2)</li>

                                 <li><span>09:25</span>(周末剧场1特播1 2')</li>

                                 <li><span>09:27</span>42集:舞乐传奇 (32)</li>

                                 <li><span>10:16</span>收视预告(3)</li>

                                 <li><span>10:18</span>(周末剧场2特播1 2')</li>

                                 <li><span>10:20</span>42集:舞乐传奇 (33)</li>

                                 <li><span>11:09</span>(周末剧场3特播1 2')</li>

                                 <li><span>11:19</span>42集:舞乐传奇 (34)</li>

                        </ul>
                    </div>
                    <div class="Clist2">
                        <ul>

                                 <li><span>12:00</span>重播:广西故事</li>

                                 <li><span>12:15</span>重播:饭好了</li>

                                 <li><span>12:50</span>收视预告(4)</li>

                                 <li><span>12:52</span>(周末剧场4特播1 2')</li>

                                 <li><span>12:55</span>42集:舞乐传奇 (35)</li>

                                 <li><span>13:45</span>收视预告(5)</li>

                                 <li><span>13:47</span>(周末剧场5特播1 2')</li>

                                 <li><span>13:49</span>42集:舞乐传奇 (36)</li>

                                 <li><span>14:39</span>收视预告(6)</li>

                                 <li><span>14:41</span>(周末剧场6特播1 2')</li>

                                 <li><span>14:43</span>42集:舞乐传奇 (37)</li>

                                 <li><span>15:33</span>收视预告(7)</li>

                                 <li><span>15:35</span>(周末剧场7特播1 2')</li>

                                 <li><span>15:37</span>42集:舞乐传奇 (38)</li>

                                 <li><span>16:28</span>风云榜前 2'</li>

                                 <li><span>16:30</span>星APP风云榜 20'</li>

                                 <li><span>17:01</span>收视预告(8)</li>

                                 <li><span>17:05</span>民族动画剧场 </li>

                                 <li><span>18:00</span>新闻大通道</li>

                                 <li><span>18:30</span>直播：广西新闻</li>

                                 <li><span>18:58</span>广西天气预报</li>

                                 <li><span>19:00</span>转播：新闻联播</li>

                                 <li><span>19:33</span>美丽(2+1)剧场:伪装者(18)</li>

                                 <li><span>20:16</span>收视指南(9)</li>

                                 <li><span>20:35</span>美丽(2+1)剧场:伪装者(19)</li>

                                 <li><span>21:17</span>收视指南(10)</li>

                                 <li><span>21:20</span>首播:收藏马未都 60'</li>

                                 <li><span>22:20</span>广西故事 15'</li>

                                 <li><span>22:35</span>收视指南(11)</li>

                                 <li><span>22:50</span>魅力剧场:雍正王朝(42)</li>

                                 <li><span>23:30</span>收视指南(12)</li>

                                 <li><span>23:40</span>时尚中国 20'</li>

                        </ul>
                    </div>
                </div>
            </div>
        </div>
    </div>
<!--foot -->
<div class="Footer">
<h2 class="Footer_T">
<span class="capname">
<a href="http://info.gxtv.cn/201209/news_13914071.html" target="_blank">关于广西网络广播电视台</a> |
<a href="#" target="_blank">联系我们</a> |
<a href="http://news.gxtv.cn/scrollnews/Scrollnews-1.html" target="_blank">最新新闻</a> |
<a href="http://www.gxtv.cn/map/" target="_blank">网站地图</a> |
<a href="#" target="_blank">广告服务</a> |
<a href="http://info.gxtv.cn/ZcrList.html" target="_blank">主持人</a> |
<a href="http://vod.gxtv.cn/" target="_blank">节目点播</a> |
<a href="http://info.gxtv.cn/" target="_blank">广西电视台</a> |
<a href="http://program.gxtv.cn/" target="_blank">节目表</a> |
<a href="http://user.gxtv.cn/" target="_blank">会员注册</a>
</span></h2>
<div class="Cont">
<p>广西电视台新媒体部编辑制作&nbsp;&nbsp;&nbsp;&nbsp;地址：中国南宁市民族大道73号(530022)&nbsp;&nbsp;电话：(0771)2196666&nbsp;&nbsp;传真：(0771)5854039 </p>
<p>广西网络广播电视台官方微博：http://t.sina.com.cn/gxnettv&nbsp;&nbsp;&nbsp;&nbsp;本站通用网址：www.gxtv.cn&nbsp;www.gxtv.com.cn&nbsp;www.mltx.cn</p>
<p>信息产业部备案号：桂ICP备05006981-1号&nbsp;&nbsp;&nbsp;&nbsp;信息网络传播视听节目许可证：2002007</p>
<p>广西网警网站备案：45010302000138号&nbsp;&nbsp;&nbsp;&nbsp;广西壮族自治区互联网新闻信息服务备案许可证编号：<a href="http://info.gxtv.cn/xukezheng.html">4510020090001</a> <script src='http://s111.cnzz.com/stat.php?id=953313&web_id=953313&show=pic1' language='JavaScript' charset='gb2312'></script></p>
<p><a href="http://www.gxtv.cn">广西网络广播电视台</a>版权所有 未经书面授权禁止复制或建立镜像</p>
<p><a href="http://www.gxpprft.gov.cn">上级行政主管部门官方网站：广西壮族自治区新闻出版广电局</a></p>
<p>
<a href="http://www.12377.cn/" target="_blank" >
<img src="http://www.gxtv.cn/images/footer_logomess.gif" alt="中国互联网违法和不良信息举报中心" border="0">
</a>
<!--  报警岗亭代码开始   -->
<a id='_gx_gangting' href="http://www.gx.cyberpolice.cn/AlarmInfo/getTishi.do?icon=gangting&checkCode=6957203721d70c65a3fc5e9e6d12fefb" target="_blank" style=" text-decoration: none; border:0; padding-top: 12px; height: 50px;width: 110px;">
<img src="http://www.gxtv.cn/images/cyberhome.gif" alt="广西网警虚拟岗亭" border="0">
</a>
<!--  报警岗亭代码结束  -->

<!--  ICP备案代码开始（以后维护此段代码可Ctrl+F查询此段注释）-->
<a id='_gx_baicp' href="http://www.gx.cyberpolice.cn/AlarmInfo/getTishi.do?icon=baicp&checkCode=6957203721d70c65a3fc5e9e6d12fefb" target="_blank" style=" text-decoration: none; border:0; padding-top: 12px; height: 50px;width: 110px;">
<img src="http://www.gxtv.cn/images/baicp.gif" alt="广西网警ICP备案" border="0" >
</a>
<!--  ICP备案代码结束 -->

<!--可信网站图片LOGO安装开始-->
<script src="https://kxlogo.knet.cn/seallogo.dll?sn=2011063000200011099&ct=df"></script>
<!--可信网站图片LOGO安装结束-->
<script type="text/javascript">document.write(unescape("%3Cspan id='_ideConac' %3E%3C/span%3E%3Cscript src='http://dcs.conac.cn/js/21/000/0000/40700506/CA210000000407005060002.js' type='text/javascript'%3E%3C/script%3E"));</script>
</p>
</div>
</div>
</body>
</html>');

    return $output;
  }

}
