<?php
// $Id$

/**
 * @file
 * Contains form definition and submission callbacks of Paypaad UI.
 */

/**
 * Form callback for Paypaad transaction delete confirmation.
 *
 * @param $form_state
 *   Known form state array.
 * @param $transaction
 *   Loaded Paypaad transaction object.
 *
 * @ingroup forms
 *
 * @see confirm_form()
 */
function paypaad_ui_delete_form(&$form_state, $transaction) {
  $form = array();
  // Inject transaction identifier into the form.
  $form['pid'] = array(
    '#type' => 'value',
    '#value' => $transaction->pid,
  );
  // Generate confirmation form array.
  return confirm_form(
    $form,
    t('Are you sure you want to delete the log of %title?', array(
      '%title' => _paypaad_ui_title($transaction)
    )),
    isset($_GET['destination']) ? $_GET['destination'] : _paypaad_ui_menu('path'),
    t('This action cannot be undone.'),
    t('Delete Transaction Log'),
    t('Cancel')
  );
}

/**
 * Form submission callback for transaction delete confirmation form.
 */
function paypaad_ui_delete_form_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    paypaad_delete((int) $form_state['values']['pid']);
    drupal_set_message(t('Paypaad transaction log has been deleted successfully.'));
  }
  // Get back to transaction administration page.
  $form_state['redirect'] = _paypaad_ui_menu('path');
}

