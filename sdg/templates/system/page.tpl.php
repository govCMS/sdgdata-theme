<?php
/**
 * @file
 * Returns the HTML for a single Drupal page.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728148
 */
?>

<div id="page-wrapper">
  <header class="header" id="header" role="banner">
    <div class="header__content">
      <div class="header__branding">
        <?php if ($logo): ?>
          <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" class="branding" id="logo"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" class="branding__logo" /></a>
        <?php endif; ?>
      </div>
      <div class="header__search">
        <?php print theme('sdg_search_form'); ?>
      </div>
    </div>
    <div class="header__menu-toggle">
      <button class="menu-toggle" role="menu" title="main menu">
        <span></span>
        <span></span>
        <span></span>
      </button>
    </div>
    <?php print render($page['header']); ?>
  </header>

  <div id="page" class="page">

    <div class="hero__wrapper constraints--hero">
      <div class="no-constraints">
        <?php  if (current_path() != 'search'): ?>
          <?php print render($page['hero']); ?>
        <?php else: ?>
          <div class="hero hero-search">
            <div class="hero__content-outer constraints">
              <div class="hero__content-inner">
                <h2 class="page-title__text">Your search</h2>
              </div>
            </div>
          </div>
        <?php endif; ?>
      </div>
    </div>

    <?php if (current_path() != 'search'): ?>
      <div class="breadcrumb__wrapper constraints">
        <div class="rss"><a href="<?php print $rss_url; ?>"><i class="fa-icon-rss"></i> Rss</a></div>
        <?php print $breadcrumb; ?>
        <?php print render($page['breadcrumb']); ?>
      </div>
    <?php endif; ?>

    <div id="main">

      <div id="content" class="column constraints" role="main">

        <a href="#skip-link" id="skip-content" class="element-invisible">Go to top of page</a>

        <?php print $messages; ?>
        <?php print render($tabs); ?>
        <?php if ($action_links): ?>
          <ul class="action-links"><?php print render($action_links); ?></ul>
        <?php endif; ?>

        <a id="main-content"></a>
        <?php print render($title_prefix); ?>
        <?php if ($title): ?>
          <h1 class="page__title title" id="page-title"><?php print $title; ?></h1>
        <?php endif; ?>
        <?php print render($title_suffix); ?>

        <?php print render($page['content']); ?>
        <?php print $feed_icons; ?>
      </div>

      <?php
        // Render the sidebars to see if there's anything in them.
        $sidebar_first  = render($page['sidebar_first']);
        $sidebar_second = render($page['sidebar_second']);
      ?>

      <?php if ($sidebar_first || $sidebar_second): ?>
        <aside class="sidebars" role="complementary">
          <?php print $sidebar_first; ?>
          <?php print $sidebar_second; ?>
        </aside>
      <?php endif; ?>

    </div>

    <div id="footer" class="footer">
      <div class="footer__top">
        <div class="footer__logo-container">
          <img src="<?php print $footer_logo; ?>" alt="Australian Government Logo" class="footer__logo" />
        </div>
        <div><?php print render($page['footer']); ?></div>
      </div>
      <div class="footer__bottom">
        <div><?php print render($page['bottom']); ?></div>
      </div>
      <div class="footer__post">
        <p class="footer__post-copy">&copy; <?php print date('Y'); ?> Australian Government</p>
      </div>
    </div>

  </div>

</div>
