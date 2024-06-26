<?php
function custom_model_completed_proposals_all()
{
	$output = "";
	$query = db_select('custom_model_proposal');
	$query->fields('custom_model_proposal');
	$query->condition('approval_status', 3);
	$query->orderBy('actual_completion_date', 'DESC');
	//$query->condition('is_completed', 1);
	$result = $query->execute();
	
	//var_dump($custom_model_abstract);die;
	if ($result->rowCount() == 0)
	{
		$output .= "Work has been completed for the following custom model. We welcome your contributions." ."<hr>";

	} //$result->rowCount() == 0
	else
	{
		$output .= "Work has been completed for the following custom model. We welcome your contributions." . "<hr>";
		$preference_rows = array();
		$i = $result->rowCount();
		while ($row = $result->fetchObject())
		{
			$proposal_id = $row->id;
			$completion_date = date("Y", $row->actual_completion_date);
			$preference_rows[] = array(
				$i,
				l($row->project_title, "custom-model/custom-model-run/" . $row->id) . t("<br><strong>(Script used: ") . $row->script_used . t(")</strong>"),
				$row->contributor_name,
				$row->university,
				$completion_date
			);
			$i--;
		} //$row = $result->fetchObject()
		$preference_header = array(
			'No',
			'Custom Model Project',
			'Contributor Name',
			'University / Institute',
			'Year of Completion'
		);
		$output .= theme('table', array(
			'header' => $preference_header,
			'rows' => $preference_rows
		));
	}
	return $output;
}
// eSim custom model display in progress proposals
function custom_model_progress_all()
{
	$page_content = "";
	$query = db_select('custom_model_proposal');
	$query->fields('custom_model_proposal');
	$query->condition('approval_status', 1);
	$query->condition('is_completed', 0);
	$query->orderBy('approval_date',DESC);
	$result = $query->execute();
	if ($result->rowCount() == 0)
	{
		$page_content .= "Work is in progress for the following custom model under DWSIM Custom Model Project<hr>";
	} //$result->rowCount() == 0
	else
	{
		$page_content .= "Work is in progress for the following custom model under DWSIM Custom Model Project<hr>";
		$preference_rows = array();
		$i = $result->rowCount();
		while ($row = $result->fetchObject())
		{
			$approval_date = date("Y", $row->approval_date);
			$preference_rows[] = array(
				$i,
				$row->project_title,
				$row->contributor_name,
				$row->university,
				$approval_date
			);
			$i--;
		} //$row = $result->fetchObject()
		$preference_header = array(
			'No',
			'Custom Model Project',
			'Contributor Name',
			'University / Institute',
			'Year'
		);
		$page_content .= theme('table', array(
			'header' => $preference_header,
			'rows' => $preference_rows
		));
	}
	return $page_content;
}