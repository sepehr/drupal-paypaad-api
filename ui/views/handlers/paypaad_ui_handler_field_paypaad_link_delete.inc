<?php

/**
 * @file
 * Implements Paypaad transaction delete link handler for views.
 */

/**
 * Field handler to provide a link to delete a Paypaad transaction log.
 */
class paypaad_ui_handler_field_paypaad_link_delete extends views_handler_field {
  /**
   * Class constructor.
   */
  function construct() {
    parent::construct();
    $this->additional_fields['pid'] = 'pid';
  }

  /**
   * Defines field options.
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['text'] = array('default' => '', 'translatable' => TRUE);
    return $options;
  }

  /**
   * Adds field options form.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['text'] = array(
      '#type' => 'textfield',
      '#title' => t('Text to display'),
      '#default_value' => $this->options['text'],
    );
  }

  /**
   * Views query handler method.
   */
  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  /**
   * Field renderer.
   */
  function render($values) {
    if (user_access('administer paypaad transactions')) {
      $text = !empty($this->options['text']) ? $this->options['text'] : t('delete');
      return l($text, _paypaad_ui_menu('path') . '/transaction/' . $values->{$this->aliases['pid']} . '/delete', array(
        'query' => drupal_get_destination(),
      ));
    }
  }
}

